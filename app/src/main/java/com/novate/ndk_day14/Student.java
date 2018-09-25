package com.novate.ndk_day14;


import android.os.Parcel;
import android.os.Parcelable;

public class Student implements Parcelable{

    @Override
    public int describeContents() {
        return 0;
    }

    /**
     * 写数据
     */
    @Override
    public void writeToParcel(Parcel dest, int flag) {
        // 先写 int 数据
        dest.writeInt(12);
        // 再写 String 数据
        dest.writeString("Novate");
    }


    /**
     * 读数据
     */
    protected Student(Parcel in) {
        // 写读 String
        in.readString();
        // 再读 int
        in.readInt();
    }

    public static final Creator<Student> CREATOR = new Creator<Student>() {
        @Override
        public Student createFromParcel(Parcel in) {
            return new Student(in);
        }

        @Override
        public Student[] newArray(int size) {
            return new Student[size];
        }
    };
}
