
#ifndef TEVENT_HANDLER_H
#define TEVENT_HANDLER_H

#include <windows.h>
//#include <SHLOBJ.H>
//#include <memory>
//#include <string>
#include "eSpace.tlh"
//#import "..\tlb\eSpace.tlb" rename_namespace("eSpace") named_guids

// Generic event handler template class (especially useful (but not limited to) for non-ATL clients).
template <class event_handler_class, typename device_interface>
class TEventHandler : eSpace::IECSEventCallback
{
    friend class class_event_handler;

    typedef HRESULT (event_handler_class::*parent_on_event)
        (
        eSpace::ECSEventType eventId,
        const _variant_t & param1,
        const _variant_t & param2,
        IUnknown * eventInfo
        );

public :
    TEventHandler
        (
        event_handler_class& parent,
        device_interface* pdevice_interface,  // Non-ref counted.
        parent_on_event parent_on_event_function
        ) :
        m_cRef(1),
        m_parent(parent),
        m_parent_on_event(parent_on_event_function)
    {
        RegistEventListener(pdevice_interface);
    }

    ~TEventHandler()
    {
        // Call ShutdownConnectionPoint() here JUST IN CASE connection points are still 
        // alive at this time. They should have been disconnected earlier.
        UnregistEventListener();
    }

    STDMETHOD_(ULONG, AddRef)()
    {
        InterlockedIncrement(&m_cRef);

        return m_cRef;  
    }

    STDMETHOD_(ULONG, Release)()
    {
        InterlockedDecrement(&m_cRef);

        if (m_cRef == 0)
        {
            delete this;
            return 0;
        }

        return m_cRef;
    }

    STDMETHOD(QueryInterface)(REFIID iid, void ** ppvObject)
    {

         if (iid == IID_IUnknown)
    {
        *ppvObject = (IUnknown*)this;
        AddRef();
        return S_OK;
    }

    if (iid == IID_IDispatch)
    {
        *ppvObject = (IDispatch*)this;
        AddRef();
        return S_OK;
    }

    if(iid == __uuidof(eSpace::IECSEventCallback))
    {
        *ppvObject = (eSpace::IECSEventCallback*)this;
        //*ppvObject = (IDispatch*)this;
        AddRef();
        return S_OK;
    }


        return E_NOINTERFACE;
    }

    STDMETHOD(GetTypeInfoCount)(UINT* pctinfo)
    {
        return E_NOTIMPL;
    }

    STDMETHOD(GetTypeInfo)(UINT itinfo, LCID lcid, ITypeInfo** pptinfo)
    {
        return E_NOTIMPL;
    }

    STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames,
        LCID lcid, DISPID* rgdispid)
    {
        return E_NOTIMPL;
    }

    STDMETHOD(Invoke)(DISPID dispidMember, REFIID riid,
        LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult,
        EXCEPINFO* pexcepinfo, UINT* puArgErr)
    {

        return E_NOTIMPL;
        //return (m_parent.*m_parent_on_event)(this, dispidMember, riid, lcid, wFlags, pdispparams, pvarResult, pexcepinfo, puArgErr);
    }

    STDMETHOD(OnEventReceived)(
        eSpace::ECSEventType eventId,
        const _variant_t & param1,
        const _variant_t & param2,
        IUnknown * eventInfo )
    {

        return (m_parent.*m_parent_on_event)(eventId, param1, param2, eventInfo);
    }

    //
    // Raw methods provided by interface
    //

    STDMETHOD(raw_OnEventReceived)(
        /*[in]*/ eSpace::ECSEventType eventId,
        /*[in]*/ VARIANT FAR * param1,
        /*[in]*/ VARIANT FAR * param2,
        IUnknown * eventInfo )
    {
		if(eventId == eSpace::APP_SHUTDOWN)
		{
			pIECSExternService->Release();
			pIECSExternService = NULL;
		}
        return OnEventReceived(eventId, param1, param2, eventInfo);
    }
protected :
    LONG						m_cRef;

    // Pertaining to the owner of this object.
    event_handler_class&		m_parent;  // Non-reference counted. This is to prevent circular references.
    parent_on_event			m_parent_on_event;

    eSpace::IECSEspaceApp *pIECSExternService;
    eSpace::IECSEventCallback *pUnknown;


    void RegistEventListener(device_interface* pdevice_interface)
    {
        pIECSExternService = NULL;
        pUnknown = NULL;
        

        // QI this object itself for its IUnknown pointer which will be used 
        // later to connect to the Connection Point of the device_interface object.
        this -> QueryInterface(__uuidof(eSpace::IECSEventCallback), (void **)&pUnknown);

        if (pUnknown)
        {
            // QI the pdevice_interface for its connection point.
            pdevice_interface -> QueryInterface (__uuidof(eSpace::IECSEspaceApp), (void**)&pIECSExternService);

            if (pIECSExternService)
            {
				pIECSExternService->RegisterEventListener(eSpace::APP_SHUTDOWN, __uuidof(eSpace::IECSEventCallback), pUnknown);

				pIECSExternService->RegisterEventListener(eSpace::LOGIN_STATE_CHANGE, __uuidof(eSpace::IECSEventCallback), pUnknown);

				pIECSExternService->RegisterEventListener(eSpace::CONTACT_STATE_CHANGE, __uuidof(eSpace::IECSEventCallback), pUnknown);
            }

            //pIUnknown -> Release();
            //pIUnknown = NULL;
        }
    }

public :

    void UnregistEventListener()
    {
		try{
			if (pIECSExternService)
			{
				pIECSExternService->UnregisterEventListener(eSpace::APP_SHUTDOWN, __uuidof(eSpace::IECSEventCallback), pUnknown);

				pIECSExternService->UnregisterEventListener(eSpace::LOGIN_STATE_CHANGE, __uuidof(eSpace::IECSEventCallback), pUnknown);

				pIECSExternService->UnregisterEventListener(eSpace::CONTACT_STATE_CHANGE, __uuidof(eSpace::IECSEventCallback), pUnknown);
			}
		}
		catch(...)
		{
		}
    }
};


#endif

