namespace project_gdi_
{
    partial class Form2
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.browserTabControl = new System.Windows.Forms.TabControl();
            this.label1 = new System.Windows.Forms.Label();
            this.targetBox = new System.Windows.Forms.Label();
            this.btnModify = new System.Windows.Forms.Button();
            this.btnOutput = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // browserTabControl
            // 
            this.browserTabControl.Location = new System.Drawing.Point(1, 30);
            this.browserTabControl.Name = "browserTabControl";
            this.browserTabControl.SelectedIndex = 0;
            this.browserTabControl.Size = new System.Drawing.Size(1032, 794);
            this.browserTabControl.TabIndex = 0;
            this.browserTabControl.SelectedIndexChanged += new System.EventHandler(this.browserTabControl_SelectedIndexChanged);
            this.browserTabControl.MouseDown += new System.Windows.Forms.MouseEventHandler(this.browserTabControl_MouseDown);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(-1, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "선택된 객체: ";
            // 
            // targetBox
            // 
            this.targetBox.AutoSize = true;
            this.targetBox.Location = new System.Drawing.Point(74, 9);
            this.targetBox.Name = "targetBox";
            this.targetBox.Size = new System.Drawing.Size(38, 12);
            this.targetBox.TabIndex = 2;
            this.targetBox.Text = "label2";
            // 
            // btnModify
            // 
            this.btnModify.Location = new System.Drawing.Point(247, 4);
            this.btnModify.Name = "btnModify";
            this.btnModify.Size = new System.Drawing.Size(75, 23);
            this.btnModify.TabIndex = 3;
            this.btnModify.Text = "수정";
            this.btnModify.UseVisualStyleBackColor = true;
            this.btnModify.Click += new System.EventHandler(this.btnModify_Click);
            // 
            // btnOutput
            // 
            this.btnOutput.Location = new System.Drawing.Point(947, 4);
            this.btnOutput.Name = "btnOutput";
            this.btnOutput.Size = new System.Drawing.Size(75, 23);
            this.btnOutput.TabIndex = 4;
            this.btnOutput.Text = "추출";
            this.btnOutput.UseVisualStyleBackColor = true;
            this.btnOutput.Click += new System.EventHandler(this.btnOutput_Click);
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1034, 824);
            this.Controls.Add(this.btnOutput);
            this.Controls.Add(this.btnModify);
            this.Controls.Add(this.targetBox);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.browserTabControl);
            this.Name = "Form2";
            this.Text = "Form2";
            this.Click += new System.EventHandler(this.Form2_Click);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Form2_KeyDown);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TabControl browserTabControl;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label targetBox;
        private System.Windows.Forms.Button btnModify;
        private System.Windows.Forms.Button btnOutput;
    }
}