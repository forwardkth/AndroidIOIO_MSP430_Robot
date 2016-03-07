package com.pas.webcam.api;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;


public class Wifiservice extends Service
{
	@Override
	public IBinder onBind(Intent arg0) 
	{
		// TODO Auto-generated method stub
		return null;
	}
	
	public void onCreate()
	{
        super.onCreate();

		
	}
	
	public int onStartCommand(Intent intent, int flags, int startId)
	{
		
        UDPserver server = new UDPserver();
        
        new Thread(server).start();
        android.util.Log.d("onCreate", "wifi Service started!");
		return START_STICKY;
		
	}
	
	public void onDestroy()
	{
		super.onDestroy();
		android.util.Log.d("onCreate", "wifi Service destroyed!");
	}

}
