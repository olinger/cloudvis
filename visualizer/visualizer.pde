import processing.net.*;

import ddf.minim.*;
import ddf.minim.analysis.*;
import ddf.minim.effects.*;
import ddf.minim.signals.*;
import ddf.minim.spi.*;
import ddf.minim.ugens.*;
import processing.core.*;

Client myClient; 

Minim minim;
AudioInput in;
FFT fft;
float[] angle;
float[] y, x;
color fill;

//client
Client client;
boolean connect = true;

BeatDetect heart = new BeatDetect();
void setup() {
  size(640, 360);
  background(255);

  minim = new Minim(this);
  in = minim.getLineIn(Minim.STEREO, 2048, 192000.0);
  fft = new FFT(in.bufferSize(), in.sampleRate());
  y = new float[fft.specSize()];
  x = new float[fft.specSize()];
  angle = new float[fft.specSize()];
  if(connect)
    client = new Client(this, "172.20.10.4",80);
   // println("saying hello");
    //client.write("hellooooo");
}

void draw() 
{
  background(0);
  heart.detect(in.mix);
  stroke(255);
    fft.forward( in.mix );
  float max = 0;
  for(int i = 0; i < fft.specSize(); i++)
  {
    if(heart.getDetectCenterFrequency(i) != 0)
    {
        /*println(i);
        println(heart.getDetectCenterFrequency(i));
        println("");*/

    }
    if(fft.getBand(i) > max)
    {
      max = fft.getBand(i);
    }
    // draw the line for frequency band i, scaling it up a bit so we can see it
    stroke(0, 0, 255);
    line( i, height, i, height - fft.getBand(i)*8 );
    
  }
  if(max >= 1 && max < 5)
  {
    fill = 50;
  }
  else if(max >= 5 && max < 9)
  {
    fill = 100;
  }
  else if(max >=9 && max < 16)
  {
    fill = 150;
  }
  else if(max >= 16 && max < 20)
  {
    fill = 200;
  }
  else if(max >=20 && max < 26)
  {
    fill = 250;
  }
  else
  {
    fill = 0;
  }
  for(int x = 0; x < 6; x++)
  {
    for(int y = 0; y < 5; y++)
    {
    if(heart.isOnset())
    {
      fill(255,255,255);
      fill = 255;
    }
    else
    {
      if(fill == 0)
        fill(255, 255, 255);
      else
        fill(fill, fill, 255);
    }
        stroke(0);
        rect(x * 70, y * 70, 70, 70);
    }
  }
 /*while(client.available() <= 0)
  {
    //wait for client
  }*/
  String message = str(fill) + '\r';
 // println(message);

   //if(client.available() > 0)
   // {
      //client.read();
      println(message);
      client.write(message);
 //     client.clear();
 // }
 // delay(1000);
  //client.write("/LED=GREEN\r");
  //client.write("r:"+fill+"g:"+fill+"b:255\r");
}

void stop()
{
 // client.write("bye\r");
   minim.stop();
   super.stop();
}