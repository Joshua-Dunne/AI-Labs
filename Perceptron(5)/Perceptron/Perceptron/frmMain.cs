using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Perceptron
{
    public partial class frmMain : Form
    {
        List<Sample> samples = new List<Sample>();
        Graphics objGraphics;
        Graphics grph;
        double w1, w2, w0 = 0;
        double eta = 0.2;
        double x0 = 1; // Bias input will always be 1. Otherwise a bias weight w0 of 0 would never increase.

        int maxIterations;

        public frmMain()
        {
            InitializeComponent();
        }

        private void picCanvas_MouseDown(object sender, MouseEventArgs e)
        {
            
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
            objGraphics = pnlCanvas.CreateGraphics();
            grph = pnlCanvas.CreateGraphics();
        }

        private void btnLearn_Click(object sender, EventArgs e)
        {
            maxIterations = int.Parse(txtIterations.Text);
            eta = (double)trackLearningRate.Value / 1000;

            w0 = 0;
            w1 = 1;
            w2 = 0.5;

            // Your code to update the weights here..
            // You want to iterate through your update process maxIteration times,
            // applyiong the Perceptron Learning Rule and updating the weights.
            // You can make use of the following to draw a line based on the new weights.
            // (Weights w0, w1 and w2 are global).
            // Do this within your loop so you can see the line converging on its correct position in the plane.

            for(int i = 0; i < maxIterations; i++)
            {
                foreach (Sample sample in samples)
                {
                    double calculation = w0 + (w1 * sample.X1) + (w2 * sample.X2);
                    int output = 0;

                    if (calculation > 0) output = 1;
                    else output = -1;
                    
                    if (sample.Class == 1) // set A
                    {
                        if (output == 1) continue; // set A looks for 1, so continue if it's right

                        // if it is incorrect, adjust weights
                        // wi = wi + eta * (d(n) - o(n)) * xi
                        w0 = w0 + eta * (1 - output) * x0;
                        w1 = w1 + eta * (1 - output) * sample.X1;
                        w2 = w2 + eta * (1 - output) * sample.X2;

                    }
                    else // set B
                    {
                        if (output == -1) continue; // set B looks for 0, so continue if it's right

                        // if it is incorrect, adjust weights
                        // wi = wi + eta * (d(n) - o(n)) * xi
                        w0 = w0 + eta * (0 - output) * x0;
                        w1 = w1 + eta * (0 - output) * sample.X1;
                        w2 = w2 + eta * (0 - output) * sample.X2;
                    }

                    objGraphics.Clear(Color.White);
                    DrawSeparationLine();
                }
            }
        }

        private void picCanvas_MouseMove(object sender, MouseEventArgs e)
        {

            double posX = (double)(e.X - pnlCanvas.Width / 2) / 10;
            double posY = (double)(pnlCanvas.Height / 2 - e.Y) / 10;

            this.Text = posX + " " + posY;
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            samples.Clear();
            objGraphics.Clear(Color.White);
            objGraphics.DrawLine(new Pen(Color.Gainsboro), new Point(0, pnlCanvas.Height / 2), new Point(pnlCanvas.Width, pnlCanvas.Height / 2));
            objGraphics.DrawLine(new Pen(Color.Gainsboro), new Point(pnlCanvas.Width / 2, 0), new Point(pnlCanvas.Width / 2, pnlCanvas.Height));
        }

        private void DrawSamples()
        {
            foreach (Sample sample in samples)
            {

                double posX = (pnlCanvas.Width / 2) + sample.X1 * 10;
                double posY = (pnlCanvas.Height / 2) - sample.X2 * 10;

                Pen pen;
                if (sample.Class == 1)
                {
                    pen = new Pen(Color.Blue);
                }
                else
                {
                    pen = new Pen(Color.Red);
                }

                objGraphics.DrawLine(pen, new Point((int)posX - 3, (int)posY), new Point((int)posX + 3, (int)posY));
                objGraphics.DrawLine(pen, new Point((int)posX, (int)posY - 3), new Point((int)posX, (int)posY + 3));
            }
        }

        private void DrawSeparationLine()
        {
            objGraphics.DrawLine(new Pen(Color.Gainsboro), new Point(0, pnlCanvas.Height / 2), new Point(pnlCanvas.Width, pnlCanvas.Height / 2));
            objGraphics.DrawLine(new Pen(Color.Gainsboro), new Point(pnlCanvas.Width / 2, 0), new Point(pnlCanvas.Width / 2, pnlCanvas.Height));

            Pen pen = new Pen(Color.DarkGreen);
            double x1;

            x1 = -10;   //Oisin: Just picks a random point to draw a line from using the weights.
            double y = -(x1 * w1 / w2) - ((x0*w0) / w2);

            double shift = pnlCanvas.Height / 2;


            Point p1 = new Point(0, (int)(shift - y * 10));

            x1 = 10;
            double y2 = -(x1 * w1 / w2) - ((w0) / w2);

            Point p2 = new Point(pnlCanvas.Width, (int)(shift - y2 * 10));
            if (w2 != 0)
            {
                objGraphics.DrawLine(pen, p1, p2);
                DrawSamples();
            }
        }

        private void trackLearningRate_Scroll(object sender, EventArgs e)
        {
            lblLearningRate.Text = "Learning Rate: " + (double)trackLearningRate.Value/1000;
        }

        private void pnlCanvas_MouseDown(object sender, MouseEventArgs e)
        {
            Sample sample;
            Pen pen;

            double posX = (double)(e.X - pnlCanvas.Width / 2) / 10;
            double posY = (double)(pnlCanvas.Height / 2 - e.Y) / 10;

            if (e.Button == MouseButtons.Left)
            {
                pen = new Pen(Color.Blue);
                sample = new Sample(posX, posY, 1);
            }
            else
            {
                pen = new Pen(Color.Red);
                sample = new Sample(posX, posY, -1);
            }
            samples.Add(sample);

            objGraphics.DrawLine(pen, new Point(e.X - 3, e.Y), new Point(e.X + 3, e.Y));
            objGraphics.DrawLine(pen, new Point(e.X, e.Y - 3), new Point(e.X, e.Y + 3));
        }

        private void pnlCanvas_Paint(object sender, PaintEventArgs e)
        {
            objGraphics.DrawLine(new Pen(Color.Gainsboro), new Point(0, pnlCanvas.Height / 2), new Point(pnlCanvas.Width, pnlCanvas.Height / 2));
            objGraphics.DrawLine(new Pen(Color.Gainsboro), new Point(pnlCanvas.Width / 2, 0), new Point(pnlCanvas.Width / 2, pnlCanvas.Height));
        }


        
    }
}
