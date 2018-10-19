# JNA vs. JNI on Windows
The project demonstrates how to use **JNA** and **JNI** to call the same native C/C++ code in a Java project on Windows. With the project, you can compare the performance between JNA and JNI, as well as figure out the cause of **Java VM Stack Overflow Exception** when running the app in 32-bit Java environment.

## Download and Installation
* [CMake](https://cmake.org/download/)
* [JNA](https://github.com/java-native-access/jna)
    
    Copy to `<Project Root>/libs`.

* [Dynamsoft Barcode Reader](https://www.dynamsoft.com/Downloads/Dynamic-Barcode-Reader-Download.aspx)

    Copy shared libraries to `<Project Root>/jni/platforms/win`:

    - DBRx64.lib
    - DBRx86.lib
    - DynamsoftBarcodeReaderx64.dll
    - DynamsoftBarcodeReaderx86.dll

    and `<Your Project Root>/jna/platforms/win`:

    - DBRx64.lib
    - DBRx86.lib
    - DynamsoftBarcodeReaderx64.dll
    - DynamsoftBarcodeReaderx86.dll

    We can test the app in both **32-bit** Java environment and **64-bit** Java environment to see the difference.

## Building DLL Files with CMake

### JNA

x86

```
cd jna
mkdir build
cd build
cmake .. 
cmake --build . --config Release --target install
```

x64

```
cd jna
mkdir build
cd build
cmake -G"Visual Studio 15 2017 Win64" .. 
cmake --build . --config Release --target install
```

### JNI

x86

```
cd jni
mkdir build
cd build
cmake .. 
cmake --build . --config Release --target install
```

x64

```
cd jni
mkdir build
cd build
cmake -G"Visual Studio 15 2017 Win64" .. 
cmake --build . --config Release --target install
```

## Building Java Project with Command Lines
To quickly compile and run Java app by switching 32-bit JDK and 64-bit JDK, we'd better use the command line tool.

Compile the project:

x86

```
"E:\Program Files (x86)\Java\jdk1.8.0_191\bin\javac.exe" -cp libs\jna-3.0.9.jar src\com\dynamsoft\*.java
```

x64

```
"E:\Program Files\Java\jdk1.8.0_191\bin\javac.exe" -cp libs\jna-3.0.9.jar src\com\dynamsoft\*.java
```

Run the app:

x86

```
"E:\Program Files (x86)\Java\jdk1.8.0_191\bin\java.exe" -cp libs\jna-3.0.9.jar;src\ com.dynamsoft.Demo
```

x64

```
"E:\Program Files\Java\jdk1.8.0_191\bin\java.exe" -cp libs\jna-3.0.9.jar;src\ com.dynamsoft.Demo
```

![Java barcode reader](https://www.codepool.biz/wp-content/uploads/2018/10/jna-jni.PNG)

## Java VM Stack Overflow Exception

You may see the Java VM stack overflow exception when running the app in x86 Java environment. 

![Java VM stack overflow exception](https://www.codepool.biz/wp-content/uploads/2018/10/jvm-stack-overflow.PNG)

The reason is the default stack size on Windows is determined by the executable (**320K for 32-bit java.exe and 1024K for 64-bit java.exe**). We can change the stack size with `-Xss` option to make the app work:

```
"E:\Program Files (x86)\Java\jdk1.8.0_191\bin\java.exe" -Xss1024 -cp libs\jna-3.0.9.jar;src\ com.dynamsoft.Demo
```

The stack size is limited. To avoid such kind of crash, the best way is to allocate memory on the heap.

## References
- https://docs.microsoft.com/en-us/windows/desktop/api/Winnt/ns-winnt-_memory_basic_information
- https://msdn.microsoft.com/en-us/library/windows/desktop/aa366902(v=vs.85).aspx
- https://docs.microsoft.com/en-us/windows/desktop/procthread/thread-stack-size
- https://msdn.microsoft.com/en-us/library/kdzttdcb.aspx?f=255&MSPPError=-2147217396
- https://docs.oracle.com/javase/8/docs/technotes/guides/troubleshoot/crashes001.html
