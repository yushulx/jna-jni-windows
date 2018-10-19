package com.dynamsoft;

public class JNIBarcode {

	static {
		System.loadLibrary("jnidbr");
	}
    
    public native int decodefile();
}
