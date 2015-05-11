using System;
using AForge.Video;
using AForge.Video.DirectShow;
using System.Drawing;

namespace EdisonCamera
{
    class Program
    {
       
        static void Main(string[] args)
        {
            new Camera();

        }
    }
    
    class Camera
    {
        private bool DeviceExist = false;
        private FilterInfoCollection videoDevices;
        private VideoCaptureDevice videoSource = null;


        private void showCamList()
        {
            try
            {
                videoDevices = new FilterInfoCollection(FilterCategory.VideoInputDevice);
                if (videoDevices.Count == 0)
                    throw new ApplicationException();

                DeviceExist = true;
                if (videoDevices.Count == 1) { 
                    Console.WriteLine(videoDevices[0].Name);
                  }
                else
                foreach (FilterInfo device in videoDevices)
                {
                    Console.WriteLine(device.Name);
                }
            }
            catch (ApplicationException)
            {
                DeviceExist = false;
                Console.WriteLine("No capture device on your system");
                Console.ReadLine();
                System.Environment.Exit(-1);
            }
        }
        public Camera()
        {
            this.showCamList();
            if (DeviceExist)
            {
                videoSource = new VideoCaptureDevice(videoDevices[0].MonikerString);
                videoSource.NewFrame += new NewFrameEventHandler(video_NewFrame);
                CloseVideoSource();
/*
 //Show all the output possibilities
                for (int i = 0; i < videoSource.VideoCapabilities.Length; i++)
                {


                    Console.WriteLine("Resolution Number " + i);
                    Console.WriteLine(videoSource.VideoCapabilities[i].FrameSize);
                }
 */
  
                videoSource.VideoResolution = videoSource.VideoCapabilities[1];
                
                //videoSource.DesiredFrameSize = new Size(160, 120);
                //videoSource.DesiredFrameRate = 10;
                videoSource.Start();
                Console.WriteLine("Everything is Okay");
                videoSource.Stop();
               // videoSource.Stop();
            }
        }
        private void video_NewFrame(object sender, NewFrameEventArgs eventArgs)
        {
            //Bitmap img = (Bitmap)eventArgs.Frame.Clone();
            //do processing here
            //send to LCD
        }
        private void CloseVideoSource()
        {
            if (!(videoSource == null))
                if (videoSource.IsRunning)
                {
                    videoSource.SignalToStop();
                    videoSource = null;
                }
        }

    }
   
}
