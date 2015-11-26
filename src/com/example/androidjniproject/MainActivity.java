package com.example.androidjniproject;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity {
	
	//declare C/C++ method
	private native String helloString(String toWhat);
	private native void showHelloString(TextView textView, String toWhat);
	private native void callDialog();
	
	private static Context mContext;
	
	//load .so
	static {
		System.loadLibrary("NativeMath");
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		TextView textView = (TextView) findViewById(R.id.textview);
		
		textView.setText(helloString("Meteoric"));
//		showHelloString(textView, "Meteoric :)");
		
		mContext = MainActivity.this;
		
		Button button_call_cpp = (Button) findViewById(R.id.button_call_cpp);
		button_call_cpp.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				callDialog();
			}
		});
	}
	
	public static void showMyDialog(String strTitle)
	{
		AlertDialog.Builder dialog = new AlertDialog.Builder(mContext);
		dialog.setTitle(strTitle);
		dialog.setMessage("Call from C++");
		
		dialog.setCancelable(false);
		
		dialog.setPositiveButton("OK", new OnClickListener() {
			
			@Override
			public void onClick(DialogInterface arg0, int arg1) {
				arg0.dismiss();
			}
		});
		
		dialog.setNegativeButton("Close", new OnClickListener() {
			
			@Override
			public void onClick(DialogInterface arg0, int arg1) {
				arg0.dismiss();
			}
		});
		
		dialog.create().show();
	}
	
}
