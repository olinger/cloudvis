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
    background(255,0,0);
  }
  stroke(255);
    fft.forward( in.right );
 
  for(int i = 0; i < fft.specSize(); i++)
  {
    // draw the line for frequency band i, scaling it up a bit so we can see it
    line( i, height, i, height - fft.getBand(i)*8 );
    
  }
}

void stop()
{
   minim.stop();
   super.stop();
}