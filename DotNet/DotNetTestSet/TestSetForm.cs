﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using DNPDotNet;
using DNP3.Interface;
using TestSetControlLibrary;

namespace DotNetTestSet
{
    public partial class TestSetForm : Form
    {
        private StackManager sm;
        private LogControlAdapter lca;

        public TestSetForm()
        {           
            InitializeComponent();

            this.sm = new StackManager();
            this.lca = new LogControlAdapter(this.logControl);
            sm.AddLogHandler(lca);            
        }        

        private void stackBrowser1_OnTcpClientAdded(TcpClientSettings s)
        {
            sm.AddTCPClient(s.name, s.level, s.timeout, s.address, s.port);                            
        }      

        private void stackBrowser1_OnAddMaster(string name, string port, FilterLevel level, MasterStackConfig config)
        {
            //create the new form
            var display = new MasterDataDisplay();
            var adapter = new DisplayAdapterDataObserver(display);
            display.Dock = DockStyle.Fill;
            TabPage page = new TabPage(name);
            this.tabControlDisplay.TabPages.Add(page);
            page.Controls.Add(display);            
            display.CommandAcceptor = sm.AddMaster(port, name, level, adapter, config);                            
        }

        private void stackBrowser1_OnRemovePort(string name)
        {
            sm.RemovePort(name);
        }

        private void stackBrowser1_OnRemoveStack(string name)
        {
            sm.RemoveStack(name);
        }
    }

    
    
}