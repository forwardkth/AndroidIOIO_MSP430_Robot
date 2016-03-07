package com.pas.webcam.api;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;
import java.net.SocketAddress;

public class UDPserver implements Runnable
{
	private DatagramSocket ds = null;
	private InetSocketAddress address = null;
	private DatagramPacket dpsend;
	private DatagramPacket dpreceive;
	
	public UDPserver()
	{						      
		try 
        {  
            this.ds = new DatagramSocket(51000); // 邦定本地端口作为客户端  
            //this.ds.setSoTimeout(2 * 5000);  
            this.address = new InetSocketAddress("192.168.2.2",51001);  
        } 
        catch (Exception e) 
        {  
            e.printStackTrace();  
        }
	}
	@Override
	public void run() 
	{
		// TODO Auto-generated method stub
		android.util.Log.d("onCreate","run");
        while(true)
        {
        	this.receive();
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
        }
			
		
	}

	
	public void send(SocketAddress address,byte[] bytes)
	{  
        try 
        {  
            this.dpsend = new DatagramPacket(bytes, bytes.length, address);  
            this.ds.send(dpsend);  
        } 
        catch (Exception e) 
        {  
            e.printStackTrace();  
        }  
    } 
	
    public void receive()
    {  
        try 
        {  
            byte[] buffer = new byte[1024];  
            dpreceive = new DatagramPacket(buffer, buffer.length);  
            this.ds.receive(dpreceive);       
            String result = new String(dpreceive.getData(),dpreceive.getOffset(),dpreceive.getLength());
            android.util.Log.d("onCreate","server recieved： " + result);
           // byte[] data = new byte[dpreceive.getLength()];  
           // System.arraycopy(dpreceive.getData(), 0, data, 0, dpreceive.getLength());   
           // android.util.Log.d("onCreate","server recieved： " + new String(data));  
        } 
        catch (Exception e)
        {  
            e.printStackTrace();  
        }  
    }  
}
