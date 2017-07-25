package com.pterabytegames.app.numb3rs;

import android.app.NativeActivity;

public class Numb3rsActivity extends NativeActivity
{
	static
	{
		System.loadLibrary("c++_shared");
		System.loadLibrary("numb3rs");
	}
}
