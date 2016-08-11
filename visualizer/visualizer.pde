import ddf.minim.*;
import ddf.minim.analysis.*;
import ddf.minim.effects.*;
import ddf.minim.signals.*;
import ddf.minim.spi.*;
import ddf.minim.ugens.*;
import processing.core.*;

Minim minim;
AudioInput in;
FFT fft;
float[] angle;
float[] y, x;
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

}      

void draw() 
{
  background(0);
  heart.detect(in.right);
  if(heart.isOnset())
  {
   // background(255,0,0);
  }
  stroke(255);
    fft.forward( in.right );
 
  for(int x = 0; x < 6; x++)
  {
    for(int y = 0; y < 5; y++)
    {
    if(heart.isRange(1,5,1))
    {
      fill(50);
    }
    else if(heart.isRange(6,9,1))
    {
      fill(100);
    }
    else if(heart.isRange(10,15,1))
    {
      fill(150);
    }
    else if(heart.isRange(16,20,1))
    {
      fill(200);
    }
    else if(heart.isRange(21,26,1))
    {
      fill(250);
    }
    if(heart.isRange(0, fft.specSize(),1))
    {
      fill(0,255,0);
    }
    else if(heart.isOnset())
    {
      fill(255,0,0);
    }
    else
    {
      fill(255);
    }
        stroke(0);
        rect(x * 70, y * 70, 70, 70);
    }
  }
  for(int i = 0; i < fft.specSize(); i++)
  {
    if(heart.getDetectCenterFrequency(i) != 0)
    {
          println(i);
    println(heart.getDetectCenterFrequency(i));
    println("");

    }
    // draw the line for frequency band i, scaling it up a bit so we can see it
    stroke(0, 0, 255);
    line( i, height, i, height - fft.getBand(i)*8 );
    
  }
  
  
}

void stop()
{
   minim.stop();
   super.stop();
}