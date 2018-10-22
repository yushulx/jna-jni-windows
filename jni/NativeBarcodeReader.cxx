#include <stdio.h>
#include <windows.h>
#include "DynamsoftBarcodeReader.h"
#include "NativeBarcodeReader.h"

typedef u_char* address;

address current_stack_base() {
  MEMORY_BASIC_INFORMATION minfo;
  address stack_bottom;
  size_t stack_size;

  VirtualQuery(&minfo, &minfo, sizeof(minfo));
  stack_bottom =  (address)minfo.AllocationBase;
  stack_size = minfo.RegionSize;
  
  while( 1 )
  {
    VirtualQuery(stack_bottom+stack_size, &minfo, sizeof(minfo));
    if ( stack_bottom == (address)minfo.AllocationBase )
      stack_size += minfo.RegionSize;
    else
      break;
  }

#ifdef _M_IA64
#endif
	
  return stack_bottom + stack_size;
}

JNIEXPORT jint JNICALL Java_com_dynamsoft_JNIBarcode_decodefile
  (JNIEnv *, jobject)
{
	// memory
	size_t sz;
	MEMORY_BASIC_INFORMATION minfo;
	VirtualQuery(&minfo, &minfo, sizeof(minfo));
	sz = (size_t)current_stack_base() - (size_t)minfo.AllocationBase;
	printf("The default Java thread stack size for this system is %u bytes(%u KB).\n", sz, sz / 1024);

	unsigned char gray[640 * 480];

	CBarcodeReader reader;
	//while (true)
	{

		// printf("Initialize the license of Dynamsoft Barcode Reader.\n");
		reader.InitLicense("t0068MgAAAEPkMiSS8ucNcLV38rMgffFHSlm1qQOuqeBkzRokcOGV2eSYmKGu4rpl6SGWRTduH7vpA52UkS5bA5+x0p23Zcc=");

		// printf("Load the parameters. \n");
		char error[512];
		reader.InitRuntimeSettingsWithFile("qr_balance.json", ECM_Overwrite, error, 512);

		// printf("Decoding starts.\n");
		int iRet = reader.DecodeBuffer(gray, 480, 640, 480, IPF_GrayScaled, "Default_Template");
		// printf("Decoding ends.\n");
	}
	return 0;
}
