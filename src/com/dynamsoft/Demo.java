package com.dynamsoft;

public class Demo {

	public static void main(String[] args) {
		int count = 1;
		
		JNABarcode jnaReader = new JNABarcode();
		
		System.out.println("JNA start.");
		long start = System.currentTimeMillis();
		for (int i = 0; i < count; i++) {
			jnaReader.decodefile();
		}
		long end = System.currentTimeMillis();
		System.out.println("JNA end. Time cost: " + (end - start) + "ms");
		
		JNIBarcode jniReader = new JNIBarcode();
		System.out.println("JNI start.");
		start = System.currentTimeMillis();
		for (int i = 0; i < count; i++) {
			jniReader.decodefile();
		}
		end = System.currentTimeMillis();
		System.out.println("JNI end. Time cost: " + (end - start) + "ms");
	}

}