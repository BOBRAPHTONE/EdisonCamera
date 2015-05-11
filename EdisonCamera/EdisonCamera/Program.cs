using System;
using System.Drawing;
using OpenCvSharp.CPlusPlus;

namespace EdisonCamera
{
    class Program
    {

        private static void Main(string[] args)
        {

            VideoCapture cap = new VideoCapture(0);
            if (!cap.IsOpened()) // if not success, exit program
            {
                Console.WriteLine("Cannot open the web cam");
                return;
            }

            while (true)
            {
                //     try
                {
                    Mat imgOriginal = new Mat();
                    cap.Read(imgOriginal); // read a new frame from video
                    //      Cv2.ImShow("Original", imgOriginal); //show the original image

                    if (Cv2.WaitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
                    {
                        Console.WriteLine("esc key is pressed by user");
                        break;
                    }
                }
                //         catch (Exception)
                {

                }
            }
        }
    }
    
    class Camera
    {
        
       
        public Camera()
        {
           
        }

    }
   
}
