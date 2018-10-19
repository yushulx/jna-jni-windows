package com.dynamsoft;

import com.sun.jna.Library;
import com.sun.jna.Native;

public class JNABarcode {

	public interface JNADBR extends Library {
		JNADBR INSTANCE = (JNADBR) Native.loadLibrary("jnadbr", JNADBR.class);

		public int decodefile();
	}

	public void decodefile() {
		JNADBR.INSTANCE.decodefile();
	}

}
