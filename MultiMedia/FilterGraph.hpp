#pragma once
#include "strmif.h"
#include "uuids.h"
#include <dshow.h>
#pragma comment (lib, "Strmiids.lib")
#include <iostream>
void enum_capture_device()
{
	CoInitialize(nullptr);
	ICreateDevEnum* p_create_dev_enum = nullptr;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, nullptr, CLSCTX_INPROC_SERVER,
		IID_ICreateDevEnum, (void**)&p_create_dev_enum);

	IEnumMoniker* p_enum_moniker = nullptr;
	hr = p_create_dev_enum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &p_enum_moniker, 0);
	p_enum_moniker->Reset();

	unsigned long ul_fetched = 0;
	IMoniker* p_moniker = nullptr;
	while (hr = p_enum_moniker->Next(1, &p_moniker, &ul_fetched), S_OK == hr)
	{
		IPropertyBag* p_property_bag = nullptr;
		p_moniker->BindToStorage(0, 0, IID_IPropertyBag, (void**)&p_property_bag);
		VARIANT var;
		VariantInit(&var);
		p_property_bag->Read(L"FriendlyName", &var, nullptr);
		char displayName[128];
		WideCharToMultiByte(CP_ACP, 0, var.bstrVal, -1, displayName, sizeof(displayName), "", nullptr);
		VariantClear(&var);
		std::cout << displayName << std::endl;
		SysFreeString(var.bstrVal);
		p_moniker->AddRef();
	}
	p_enum_moniker->Release();
	p_create_dev_enum->Release();

	CoUninitialize();
}

#include <atlcomcli.h>
void init_cap_filter()
{
	IGraphBuilder* ptr_graph_builder = nullptr; ICaptureGraphBuilder2* ptr_capture_builder = nullptr; 
	HRESULT hr = CoCreateInstance(CLSID_FilterGraph, nullptr, CLSCTX_INPROC_SERVER, 
		IID_IGraphBuilder, (void**)(&ptr_graph_builder));
	hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, nullptr, CLSCTX_INPROC_SERVER,
		IID_ICaptureGraphBuilder2, (void**)(&ptr_capture_builder));

	IMediaControl* ptr_media_control = nullptr;
	hr = ptr_graph_builder->QueryInterface(IID_IMediaControl, (void**)(&ptr_media_control));
	IVideoWindow* ptr_video_window = nullptr;
	hr = ptr_graph_builder->QueryInterface(IID_IVideoWindow, (void**)(&ptr_video_window));

	ptr_capture_builder->SetFiltergraph(ptr_graph_builder);	
}

void open_cap_device()
{
	IBaseFilter* ptr_base_filter;
	//HRESULT hr = CoCreateInstance(CLSID_SampleGrabber,
}