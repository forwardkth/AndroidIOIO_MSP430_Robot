package com.pas.webcam.api;

import android.util.Log;
import ioio.lib.api.DigitalOutput;
import ioio.lib.api.IOIO;
import ioio.lib.api.IOIOFactory;
import ioio.lib.api.exception.ConnectionLostException;
import ioio.lib.api.exception.IncompatibilityException;

public class IOIOthread implements Runnable 
{
	private DigitalOutput led_ = null;
	private IOIO ioio_ = null;
	private boolean abort_ = false;
	private boolean connected_ = true;
	
	public IOIOthread()
	{						      

	}
	@Override
	public void run()
	{
		while(true)
		{
			try {				
					if (abort_) {
						break;
					}
					ioio_ = IOIOFactory.create();
					android.util.Log.d("onCreate", "IOIO Service in Run!");
				
				try {
					ioio_.waitForConnect();
				} catch (IncompatibilityException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				connected_ = true;
				//setup();
				led_ = ioio_.openDigitalOutput(0, true);
				while (!abort_) {
				//	loop();
					android.util.Log.d("onCreate", "looping");
					led_.write(false);
					
					try {
						Thread.sleep(1000);
					} catch (InterruptedException e) {
					}

         			led_.write(true);
         			
					try {
						Thread.sleep(1000);
					} catch (InterruptedException e) {
					}
						
				}
				ioio_.disconnect();
			} catch (ConnectionLostException e) {
				if (abort_) {
					break;
				}
			} 
				// nothing to do - just wait until physical disconnection
				try {
					ioio_.waitForDisconnect();
				} catch (InterruptedException e1) {
					ioio_.disconnect();
				}
			 catch (Exception e) {
				Log.e("AbstractIOIOActivity",
						"Unexpected exception caught", e);
				ioio_.disconnect();
				break;
			} 
		finally {
				try {
					if (ioio_ != null) {
						ioio_.waitForDisconnect();
						if (connected_) {
							ioio_.disconnect();
						}
					}
				} catch (InterruptedException e) {
				}
			}
		}																		
	}	
}


