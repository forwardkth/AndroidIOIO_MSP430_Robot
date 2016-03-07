package com.pas.webcam.api;



import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import ioio.lib.api.DigitalOutput;
import ioio.lib.api.exception.ConnectionLostException;

/**
 * An example IOIO service. While this service is alive, it will attempt to
 * connect to a IOIO and blink the LED. A notification will appear on the
 * notification bar, enabling the user to stop the service.
 */
public class HelloIOIOService extends Service
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
		IOIOthread ioio = new IOIOthread();       
        new Thread(ioio).start();
				
        android.util.Log.d("onCreate", "IOIO Service started!");
    
		return START_STICKY;
		
	}
	
	public void onDestroy()
	{
		super.onDestroy();
		android.util.Log.d("onCreate", "IOIO Service destroyed!");
	}

}
