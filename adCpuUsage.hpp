// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'adCpuUsage.pas' rev: 6.00

#ifndef adCpuUsageHPP
#define adCpuUsageHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adcpuusage
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern PACKAGE int __fastcall GetCPUCount(void);
extern PACKAGE void __fastcall ReleaseCPUData(void);
extern PACKAGE double __fastcall GetCPUUsage(int Index);
extern PACKAGE void __fastcall CollectCPUData(void);

}	/* namespace Adcpuusage */
using namespace Adcpuusage;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// adCpuUsage
