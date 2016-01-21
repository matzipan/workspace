<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xc9500xl" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="LR" />
        <signal name="RR" />
        <signal name="BW" />
        <signal name="LT" />
        <signal name="RT" />
        <signal name="BK" />
        <signal name="FW" />
        <signal name="LM0" />
        <signal name="LM1" />
        <signal name="RM0" />
        <signal name="RM1" />
        <signal name="XLXN_1539" />
        <signal name="XLXN_1512" />
        <signal name="LMB" />
        <signal name="Q0" />
        <signal name="Q1" />
        <signal name="Q2" />
        <signal name="Q3" />
        <signal name="Q4" />
        <port polarity="Input" name="LR" />
        <port polarity="Input" name="RR" />
        <port polarity="Input" name="BW" />
        <port polarity="Input" name="LT" />
        <port polarity="Input" name="RT" />
        <port polarity="Input" name="BK" />
        <port polarity="Input" name="FW" />
        <port polarity="Output" name="LM0" />
        <port polarity="Output" name="LM1" />
        <port polarity="Output" name="RM0" />
        <port polarity="Output" name="RM1" />
        <port polarity="Output" name="Q0" />
        <port polarity="Output" name="Q1" />
        <port polarity="Output" name="Q2" />
        <port polarity="Output" name="Q3" />
        <port polarity="Output" name="Q4" />
        <blockdef name="or7">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="72" y1="-256" y2="-256" x1="0" />
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="48" y1="-128" y2="-128" x1="0" />
            <line x2="48" y1="-192" y2="-192" x1="0" />
            <line x2="48" y1="-320" y2="-320" x1="0" />
            <line x2="48" y1="-448" y2="-448" x1="0" />
            <line x2="48" y1="-384" y2="-384" x1="0" />
            <line x2="192" y1="-256" y2="-256" x1="256" />
            <arc ex="112" ey="-304" sx="192" sy="-256" r="88" cx="116" cy="-216" />
            <line x2="48" y1="-208" y2="-208" x1="112" />
            <arc ex="192" ey="-256" sx="112" sy="-208" r="88" cx="116" cy="-296" />
            <line x2="48" y1="-304" y2="-304" x1="112" />
            <line x2="48" y1="-448" y2="-304" x1="48" />
            <line x2="48" y1="-64" y2="-208" x1="48" />
            <arc ex="48" ey="-304" sx="48" sy="-208" r="56" cx="16" cy="-256" />
        </blockdef>
        <blockdef name="or3">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="72" y1="-128" y2="-128" x1="0" />
            <line x2="48" y1="-192" y2="-192" x1="0" />
            <line x2="192" y1="-128" y2="-128" x1="256" />
            <arc ex="192" ey="-128" sx="112" sy="-80" r="88" cx="116" cy="-168" />
            <arc ex="48" ey="-176" sx="48" sy="-80" r="56" cx="16" cy="-128" />
            <line x2="48" y1="-64" y2="-80" x1="48" />
            <line x2="48" y1="-192" y2="-176" x1="48" />
            <line x2="48" y1="-80" y2="-80" x1="112" />
            <arc ex="112" ey="-176" sx="192" sy="-128" r="88" cx="116" cy="-88" />
            <line x2="48" y1="-176" y2="-176" x1="112" />
        </blockdef>
        <blockdef name="or2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="192" y1="-96" y2="-96" x1="256" />
            <arc ex="192" ey="-96" sx="112" sy="-48" r="88" cx="116" cy="-136" />
            <arc ex="48" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <line x2="48" y1="-144" y2="-144" x1="112" />
            <arc ex="112" ey="-144" sx="192" sy="-96" r="88" cx="116" cy="-56" />
            <line x2="48" y1="-48" y2="-48" x1="112" />
        </blockdef>
        <blockdef name="or4">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="48" y1="-256" y2="-256" x1="0" />
            <line x2="192" y1="-160" y2="-160" x1="256" />
            <arc ex="112" ey="-208" sx="192" sy="-160" r="88" cx="116" cy="-120" />
            <line x2="48" y1="-208" y2="-208" x1="112" />
            <line x2="48" y1="-112" y2="-112" x1="112" />
            <line x2="48" y1="-256" y2="-208" x1="48" />
            <line x2="48" y1="-64" y2="-112" x1="48" />
            <arc ex="48" ey="-208" sx="48" sy="-112" r="56" cx="16" cy="-160" />
            <arc ex="192" ey="-160" sx="112" sy="-112" r="88" cx="116" cy="-200" />
        </blockdef>
        <blockdef name="buf">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
            <line x2="64" y1="-64" y2="0" x1="64" />
            <line x2="64" y1="-32" y2="-64" x1="128" />
            <line x2="128" y1="0" y2="-32" x1="64" />
        </blockdef>
        <block symbolname="or4" name="XLXI_409">
            <blockpin signalname="XLXN_1512" name="I0" />
            <blockpin signalname="RT" name="I1" />
            <blockpin signalname="LR" name="I2" />
            <blockpin signalname="FW" name="I3" />
            <blockpin signalname="RM0" name="O" />
        </block>
        <block symbolname="or3" name="XLXI_412">
            <blockpin signalname="BW" name="I0" />
            <blockpin signalname="RR" name="I1" />
            <blockpin signalname="XLXN_1512" name="I2" />
            <blockpin signalname="RM1" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_362">
            <blockpin signalname="BK" name="I0" />
            <blockpin signalname="LT" name="I1" />
            <blockpin signalname="XLXN_1512" name="O" />
        </block>
        <block symbolname="or4" name="XLXI_413">
            <blockpin signalname="LMB" name="I0" />
            <blockpin signalname="LT" name="I1" />
            <blockpin signalname="RR" name="I2" />
            <blockpin signalname="FW" name="I3" />
            <blockpin signalname="LM0" name="O" />
        </block>
        <block symbolname="or3" name="XLXI_414">
            <blockpin signalname="BW" name="I0" />
            <blockpin signalname="LR" name="I1" />
            <blockpin signalname="LMB" name="I2" />
            <blockpin signalname="LM1" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_360">
            <blockpin signalname="BK" name="I0" />
            <blockpin signalname="RT" name="I1" />
            <blockpin signalname="LMB" name="O" />
        </block>
        <block symbolname="or7" name="XLXI_327">
            <blockpin signalname="BK" name="I0" />
            <blockpin signalname="RT" name="I1" />
            <blockpin signalname="LT" name="I2" />
            <blockpin signalname="RR" name="I3" />
            <blockpin signalname="LR" name="I4" />
            <blockpin signalname="FW" name="I5" />
            <blockpin signalname="BW" name="I6" />
            <blockpin signalname="Q0" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_424">
            <blockpin signalname="BW" name="I0" />
            <blockpin signalname="FW" name="I1" />
            <blockpin signalname="Q1" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_426">
            <blockpin signalname="RR" name="I0" />
            <blockpin signalname="LR" name="I1" />
            <blockpin signalname="Q2" name="O" />
        </block>
        <block symbolname="or2" name="XLXI_427">
            <blockpin signalname="RT" name="I0" />
            <blockpin signalname="LT" name="I1" />
            <blockpin signalname="Q3" name="O" />
        </block>
        <block symbolname="buf" name="XLXI_428">
            <blockpin signalname="BK" name="I" />
            <blockpin signalname="Q4" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="2688" height="1900">
        <attr value="CM" name="LengthUnitName" />
        <attr value="4" name="GridsPerUnit" />
        <text style="fontsize:24;fontname:Arial" x="59" y="744">Forward</text>
        <text style="fontsize:24;fontname:Arial" x="43" y="980">Backward</text>
        <text style="fontsize:24;fontname:Arial" x="63" y="824">Left Rotate</text>
        <text style="fontsize:24;fontname:Arial" x="47" y="904">Right Rotate</text>
        <text style="fontsize:24;fontname:Arial" x="79" y="1128">Right Turn</text>
        <text style="fontsize:24;fontname:Arial" x="79" y="1192">Braking</text>
        <text style="fontsize:24;fontname:Arial" x="79" y="1060">Left Turn</text>
        <branch name="LR">
            <wire x2="451" y1="820" y2="820" x1="243" />
        </branch>
        <branch name="RR">
            <wire x2="451" y1="900" y2="900" x1="243" />
        </branch>
        <branch name="BW">
            <wire x2="451" y1="980" y2="980" x1="243" />
        </branch>
        <branch name="LT">
            <wire x2="451" y1="1060" y2="1060" x1="243" />
        </branch>
        <branch name="RT">
            <wire x2="451" y1="1124" y2="1124" x1="243" />
        </branch>
        <branch name="BK">
            <wire x2="451" y1="1188" y2="1188" x1="243" />
        </branch>
        <branch name="FW">
            <wire x2="451" y1="740" y2="740" x1="243" />
        </branch>
        <branch name="LR">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="995" y="1348" type="branch" />
            <wire x2="1075" y1="1348" y2="1348" x1="995" />
        </branch>
        <branch name="RT">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="995" y="1412" type="branch" />
            <wire x2="1075" y1="1412" y2="1412" x1="995" />
        </branch>
        <branch name="RT">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="691" y="884" type="branch" />
            <wire x2="723" y1="884" y2="884" x1="691" />
        </branch>
        <branch name="BK">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="691" y="948" type="branch" />
            <wire x2="723" y1="948" y2="948" x1="691" />
        </branch>
        <branch name="BK">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="739" y="1572" type="branch" />
            <wire x2="771" y1="1572" y2="1572" x1="739" />
        </branch>
        <branch name="LT">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="739" y="1508" type="branch" />
            <wire x2="771" y1="1508" y2="1508" x1="739" />
        </branch>
        <branch name="BW">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="995" y="1108" type="branch" />
            <wire x2="1043" y1="1108" y2="1108" x1="995" />
        </branch>
        <branch name="LR">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="995" y="1044" type="branch" />
            <wire x2="1043" y1="1044" y2="1044" x1="995" />
        </branch>
        <branch name="LT">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="963" y="820" type="branch" />
            <wire x2="1059" y1="820" y2="820" x1="963" />
        </branch>
        <branch name="RR">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="963" y="756" type="branch" />
            <wire x2="1059" y1="756" y2="756" x1="963" />
        </branch>
        <branch name="FW">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="963" y="692" type="branch" />
            <wire x2="1059" y1="692" y2="692" x1="963" />
        </branch>
        <branch name="BW">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="995" y="1748" type="branch" />
            <wire x2="1075" y1="1748" y2="1748" x1="995" />
        </branch>
        <branch name="RR">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="995" y="1684" type="branch" />
            <wire x2="1075" y1="1684" y2="1684" x1="995" />
        </branch>
        <branch name="LM0">
            <wire x2="1539" y1="788" y2="788" x1="1315" />
        </branch>
        <branch name="LM1">
            <wire x2="1523" y1="1044" y2="1044" x1="1299" />
        </branch>
        <branch name="RM0">
            <wire x2="1587" y1="1380" y2="1380" x1="1331" />
        </branch>
        <branch name="RM1">
            <wire x2="1587" y1="1684" y2="1684" x1="1331" />
        </branch>
        <instance x="1075" y="1540" name="XLXI_409" orien="R0" />
        <text x="1039" y="1308">Forward</text>
        <branch name="FW">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="995" y="1284" type="branch" />
            <wire x2="1075" y1="1284" y2="1284" x1="995" />
        </branch>
        <instance x="1075" y="1812" name="XLXI_412" orien="R0" />
        <branch name="XLXN_1512">
            <wire x2="1043" y1="1540" y2="1540" x1="1027" />
            <wire x2="1043" y1="1540" y2="1620" x1="1043" />
            <wire x2="1075" y1="1620" y2="1620" x1="1043" />
            <wire x2="1075" y1="1476" y2="1476" x1="1043" />
            <wire x2="1043" y1="1476" y2="1540" x1="1043" />
        </branch>
        <text x="1039" y="1720">Backward</text>
        <instance x="771" y="1636" name="XLXI_362" orien="R0" />
        <text x="759" y="1536">Brake</text>
        <instance x="1059" y="948" name="XLXI_413" orien="R0" />
        <instance x="1043" y="1172" name="XLXI_414" orien="R0" />
        <text x="1003" y="1076">Backward</text>
        <branch name="LMB">
            <wire x2="995" y1="916" y2="916" x1="979" />
            <wire x2="995" y1="916" y2="980" x1="995" />
            <wire x2="1043" y1="980" y2="980" x1="995" />
            <wire x2="995" y1="884" y2="916" x1="995" />
            <wire x2="1059" y1="884" y2="884" x1="995" />
        </branch>
        <text x="1023" y="732">Forward</text>
        <text x="867" y="864">Brake</text>
        <instance x="723" y="1012" name="XLXI_360" orien="R0" />
        <iomarker fontsize="28" x="243" y="820" name="LR" orien="R180" />
        <iomarker fontsize="28" x="243" y="900" name="RR" orien="R180" />
        <iomarker fontsize="28" x="243" y="740" name="FW" orien="R180" />
        <iomarker fontsize="28" x="243" y="980" name="BW" orien="R180" />
        <iomarker fontsize="28" x="243" y="1060" name="LT" orien="R180" />
        <iomarker fontsize="28" x="243" y="1124" name="RT" orien="R180" />
        <iomarker fontsize="28" x="243" y="1188" name="BK" orien="R180" />
        <iomarker fontsize="28" x="1587" y="1380" name="RM0" orien="R0" />
        <iomarker fontsize="28" x="1587" y="1684" name="RM1" orien="R0" />
        <iomarker fontsize="28" x="1539" y="788" name="LM0" orien="R0" />
        <iomarker fontsize="28" x="1523" y="1044" name="LM1" orien="R0" />
        <branch name="Q0">
            <attrtext style="alignment:SOFT-LEFT;fontsize:28;fontname:Arial" attrname="Name" x="515" y="244" type="branch" />
            <wire x2="499" y1="244" y2="244" x1="451" />
            <wire x2="515" y1="244" y2="244" x1="499" />
        </branch>
        <branch name="BK">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="147" y="436" type="branch" />
            <wire x2="163" y1="436" y2="436" x1="147" />
            <wire x2="195" y1="436" y2="436" x1="163" />
        </branch>
        <branch name="RT">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="147" y="372" type="branch" />
            <wire x2="163" y1="372" y2="372" x1="147" />
            <wire x2="195" y1="372" y2="372" x1="163" />
        </branch>
        <branch name="LT">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="147" y="308" type="branch" />
            <wire x2="163" y1="308" y2="308" x1="147" />
            <wire x2="195" y1="308" y2="308" x1="163" />
        </branch>
        <branch name="RR">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="147" y="244" type="branch" />
            <wire x2="163" y1="244" y2="244" x1="147" />
            <wire x2="195" y1="244" y2="244" x1="163" />
        </branch>
        <branch name="LR">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="147" y="180" type="branch" />
            <wire x2="163" y1="180" y2="180" x1="147" />
            <wire x2="195" y1="180" y2="180" x1="163" />
        </branch>
        <branch name="FW">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="147" y="116" type="branch" />
            <wire x2="163" y1="116" y2="116" x1="147" />
            <wire x2="195" y1="116" y2="116" x1="163" />
        </branch>
        <branch name="BW">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="147" y="52" type="branch" />
            <wire x2="163" y1="52" y2="52" x1="147" />
            <wire x2="195" y1="52" y2="52" x1="163" />
        </branch>
        <instance x="195" y="500" name="XLXI_327" orien="R0" />
        <branch name="Q0">
            <wire x2="819" y1="164" y2="164" x1="691" />
        </branch>
        <iomarker fontsize="28" x="819" y="164" name="Q0" orien="R0" />
        <instance x="1600" y="192" name="XLXI_424" orien="R0" />
        <branch name="FW">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="1488" y="64" type="branch" />
            <wire x2="1600" y1="64" y2="64" x1="1488" />
        </branch>
        <branch name="BW">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="1488" y="128" type="branch" />
            <wire x2="1600" y1="128" y2="128" x1="1488" />
        </branch>
        <instance x="1600" y="352" name="XLXI_426" orien="R0" />
        <branch name="LR">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="1488" y="224" type="branch" />
            <wire x2="1600" y1="224" y2="224" x1="1488" />
        </branch>
        <branch name="RR">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="1488" y="288" type="branch" />
            <wire x2="1600" y1="288" y2="288" x1="1488" />
        </branch>
        <instance x="1600" y="512" name="XLXI_427" orien="R0" />
        <branch name="LT">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="1488" y="384" type="branch" />
            <wire x2="1600" y1="384" y2="384" x1="1488" />
        </branch>
        <branch name="RT">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="1488" y="448" type="branch" />
            <wire x2="1600" y1="448" y2="448" x1="1488" />
        </branch>
        <branch name="Q1">
            <wire x2="1888" y1="96" y2="96" x1="1856" />
        </branch>
        <iomarker fontsize="28" x="1888" y="96" name="Q1" orien="R0" />
        <branch name="Q2">
            <wire x2="1888" y1="256" y2="256" x1="1856" />
        </branch>
        <iomarker fontsize="28" x="1888" y="256" name="Q2" orien="R0" />
        <branch name="Q3">
            <wire x2="1888" y1="416" y2="416" x1="1856" />
        </branch>
        <iomarker fontsize="28" x="1888" y="416" name="Q3" orien="R0" />
        <branch name="BK">
            <attrtext style="alignment:SOFT-RIGHT;fontsize:28;fontname:Arial" attrname="Name" x="1664" y="544" type="branch" />
            <wire x2="1840" y1="544" y2="544" x1="1664" />
        </branch>
        <instance x="1840" y="576" name="XLXI_428" orien="R0" />
        <branch name="Q4">
            <wire x2="2096" y1="544" y2="544" x1="2064" />
        </branch>
        <iomarker fontsize="28" x="2096" y="544" name="Q4" orien="R0" />
    </sheet>
</drawing>