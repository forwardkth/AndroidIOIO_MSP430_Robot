package com.pas.webcam.api;

import com.pas.webcam.sdk.R;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class ApiTest extends Activity 
{
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        android.util.Log.d("onCreate", "program started!");
        setContentView(R.layout.main);
        ((Button)findViewById(R.id.button1)).setOnClickListener(new OnClickListener() 
        {
			@Override
			public void onClick(View v) {
				Intent launcher = new Intent().setAction(Intent.ACTION_MAIN).addCategory(Intent.CATEGORY_HOME);
				Intent ipwebcam = 
					new Intent()
					.setClassName("com.pas.webcam", "com.pas.webcam.Rolling")
					.putExtra("cheats", new String[] 
							{ 
							"set(Photo,1024,768)",         // set photo resolution to 1024x768
							"set(DisableVideo,true)",      // Disable video streaming (only photo and immediate photo)
							"reset(Port)",                 // Use default port 8080
							"set(HtmlPath,/sdcard/html/)", // Override server pages with ones in this directory 
							})
					.putExtra("hidebtn1", true)                // Hide help button
					.putExtra("caption2", "Run in background") // Change caption on "Actions..."
					.putExtra("intent2", launcher)             // And give button another purpose
				    .putExtra("returnto", new Intent().setClassName(ApiTest.this,ApiTest.class.getName())); // Set activity to return to
				startActivity(ipwebcam);
			}
		});
        
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
  // Button for start the UDP server service
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ((Button)findViewById(R.id.button2)).setOnClickListener(new OnClickListener() 
        {
			@Override
			public void onClick(View v) {
				Intent intent = new Intent();
				intent.setClass(ApiTest.this, Wifiservice.class);
				startService(intent);

			}
		});
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
        // Button for start the UDP server service
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
              ((Button)findViewById(R.id.button3)).setOnClickListener(new OnClickListener() 
              {
      			@Override
      			public void onClick(View v) {
      				Intent intent = new Intent();
      				intent.setClass(ApiTest.this, Wifiservice.class);
      				stopService(intent);

      			}
      		});       
              
              //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
              // Button for start the IOIO service
              ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    ((Button)findViewById(R.id.button4)).setOnClickListener(new OnClickListener() 
                    {
            			@Override
            			public void onClick(View v) {
            				Intent intent = new Intent();
            				intent.setClass(ApiTest.this, HelloIOIOService.class);
            				startService(intent);

            			}
            		});  
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
                    // Button for stop the IOIO service
                    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                          ((Button)findViewById(R.id.button5)).setOnClickListener(new OnClickListener() 
                          {
                  			@Override
                  			public void onClick(View v) {
                  				Intent intent = new Intent();
                  				intent.setClass(ApiTest.this, HelloIOIOService.class);
                  				stopService(intent);
                  			}
                  		});  

    }  
}