package com.novate.ndk_day14

public class Parcel{

    // 表示 long类型 = 0
    private var mNativePtr: Long  = 0
    init {
        System.loadLibrary("native-lib")

        // 初始化时候 就创建
        mNativePtr = nativeCreate()
    }

    fun writeInt(value: Int) {
        nativeWriteInt(mNativePtr, value)
    }

    fun setDataPosition(dataPos: Int) {
        nativeSetDataPosition(mNativePtr, dataPos)
    }

    fun readInt():Int{
        return nativeReadInt(mNativePtr)
    }

    // native方法，
    // 在 c层构建一个 Parcel.cpp对象，然后返回指针地址
    private external fun nativeCreate(): Long
    // 给 共享内存中 写int数据
    private external fun nativeWriteInt(mNativePtr: Long, value: Int)
    // 写 完数据之后 重新设置偏移位置
    private external fun nativeSetDataPosition(mNativePtr: Long, dataPost: Any)
    // 从 共享内存中 读int数据
    private external fun nativeReadInt(mNativePtr: Long):Int
}