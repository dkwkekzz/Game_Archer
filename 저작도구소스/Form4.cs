using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using NAudio.Wave;

namespace project_gdi_
{
    public partial class Form4 : Form
    {
        //WaveFileWriter writer;

        private DirectSoundOut output = null;

        private BlockAlignReductionStream stream = null;

        string tempPath = System.Environment.CurrentDirectory;

        public Form4()
        {
            InitializeComponent();

        }

        public byte[] ReadFile(string fileName)
        {
            string tempFile = Path.Combine(System.Environment.CurrentDirectory, fileName);

            byte[] data = new byte[1000];
            using (WaveFileReader wave = new WaveFileReader(tempFile))
            {
                int read = wave.Read(data, 0, data.Length);

                for (int i = 0; i < read; i += 2)
                {
                    System.Console.WriteLine(BitConverter.ToInt16(data, i));
                }
            }

            return data;
        }

        public void CreateFile()
        {
            string tempFile = Path.Combine(System.Environment.CurrentDirectory, "1.wav");
            WaveFormat waveFormat = new WaveFormat(8000, 8, 2);

            byte[] samples = ReadFile("test.wav");
            using (WaveFileWriter writer = new WaveFileWriter(tempFile, waveFormat))
            {
                writer.Write(samples, 0, samples.Length);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog open = new OpenFileDialog();
            open.Filter = "Wave File (*.wav)|*.wav;";
            if (open.ShowDialog() != DialogResult.OK) return;

            WaveChannel32 wave = new WaveChannel32(new WaveFileReader(open.FileName));
            EffectStream effect = new EffectStream(wave);
            stream = new BlockAlignReductionStream(effect);

            output = new DirectSoundOut(200);
            output.Init(stream);
            output.Play();
        }

        public static void TrimWavFile(string inPath, string outPath, TimeSpan cutFromStart, TimeSpan cutFromEnd)
        {
            using (WaveFileReader reader = new WaveFileReader(inPath))
            {
                using (WaveFileWriter writer = new WaveFileWriter(outPath, reader.WaveFormat))
                {
                    int bytesPerMillisecond = reader.WaveFormat.AverageBytesPerSecond / 1000;

                    int startPos = (int)cutFromStart.TotalMilliseconds * bytesPerMillisecond;
                    startPos = startPos - startPos % reader.WaveFormat.BlockAlign;

                    int endBytes = (int)cutFromEnd.TotalMilliseconds * bytesPerMillisecond;
                    endBytes = endBytes - endBytes % reader.WaveFormat.BlockAlign;
                    int endPos = (int)reader.Length - endBytes;

                    TrimWavFile(reader, writer, startPos, endPos);
                }
            }
        }

        private static void TrimWavFile(WaveFileReader reader, WaveFileWriter writer, int startPos, int endPos)
        {
            reader.Position = startPos;
            byte[] buffer = new byte[1024];
            while (reader.Position < endPos)
            {
                int bytesRequired = (endPos - (int)reader.Position);
                if (bytesRequired > 0)
                {
                    int bytesToRead = Math.Min(bytesRequired, buffer.Length);
                    int bytesRead = reader.Read(buffer, 0, bytesToRead);
                    if (bytesRead > 0)
                    {
                        writer.Write(buffer, 0, bytesRead);
                    }
                }
            }
        }
        
        private void button2_Click_1(object sender, EventArgs e)
        {
            FileInfo fi = new FileInfo(Path.Combine(tempPath, "audio_1.wav"));
            if (!fi.Exists)
            {
                MessageBox.Show("파일없음: audio_1를 넣으세요.");
                return;
            }
            fi = new FileInfo(Path.Combine(tempPath, "audio_1_mr.wav"));
            if (!fi.Exists)
            {
                MessageBox.Show("audio_1_mr을 넣으세요.");
                return;
            }

            double start = 0;
            double end = 0;
            double total = 0;
            int count = 0;
            try
            {
                start = Convert.ToDouble(startBox.Text);
                end   = Convert.ToDouble(endBox.Text);
                count = Convert.ToInt32(countBox.Text);
                total = Convert.ToDouble(totalBox.Text);
            }
            catch (Exception ex)
            {
                MessageBox.Show("텍스트박스예외: " + ex.Data);
            }

            //TrimWavFile(Path.Combine(tempPath, "audio_1.wav"), Path.Combine(tempPath, "1.wav"),
            //    new TimeSpan(0, 0, 6), new TimeSpan(0, 0, 50));
            var mStart = (int)(start * 1000);
            var mEnd = (int)(end * 1000);
            var mTotal = (int)(total * 1000);
            var length = (mEnd - mStart) / count;
            for (int i = 1, ms = mStart; ms + length <= mTotal; i++, ms += length)
            {
                TrimWavFile(Path.Combine(tempPath, "audio_1.wav"), Path.Combine(tempPath, i + ".wav"),
                new TimeSpan(0, 0, 0, 0, ms), new TimeSpan(0, 0, 0, 0, mTotal - (ms + length)));
            }
            //TrimWavFile(Path.Combine(tempPath, "audio_1_mr.wav"), Path.Combine(tempPath, i + ".wav"),
            //new TimeSpan(0, 0, ms), new TimeSpan(0, 0, ms + length));
        }
    }
}
