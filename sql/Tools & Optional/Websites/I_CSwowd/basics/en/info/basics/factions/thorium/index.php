<? $Offset = '../../../../'; ?>
<? $Offsetpic = '../../../../'; ?>
<? include $Offset."../setup/eng.php"; ?>
<? include $Offset."header.php"; ?>
<style type="text/css">
#cnt { width: 713px; height: auto; }
</style>

<? include $Offset."center.php"; ?>







<style type="text/css">

#contents{
visibility: hidden;
position: absolute;
Z-INDEX: 999999;
width: 5px;
filter:progid:DXImageTransform.Microsoft.AlphaImageLoader(enabled=true, sizingMethod=scale src='../../../../../shared/wow-com/images/backgrounds/blue-bg.png');
}
#dynamicTooltip{
visibility: hidden;
position: absolute;
Z-INDEX: 999999;
}
#tooltipText{
visibility: hidden;
color: #ffffff;
font-family: verdana, arial, sans-serif;
font-size:8pt;
font-weight:normal;
padding: 4px;
white-space:nowrap;
}
.trans_div {
/* This is an IE filter command. Other browsers will ignore it */
/* It goes into the trans_div class */
}
.trans_div[class] {
background-image:url(../../../../../shared/wow-com/images/backgrounds/blue-bg.png);
}

</style>
<div id="contents">
                        <table cellspacing = "0" cellpadding = "0" border = "0" width = "100%">
                          <tr>
                                <td width = "1" height = "1"></td>
                                <td bgcolor = "#ffffff" height = "1"><img src = "../../../../../wow-com/images/layout/pixel.html" width = "1" height = "1"></td>
                                <td width = "1" height = "1"></td>
                          </tr>
                          <tr>
                                <td bgcolor = "#A5A5A5" width = "1"><img src = "../../../../../wow-com/images/layout/pixel.html" width = "1" height = "1"></td>
                                <td valign = "top" class="trans_div"><div id="tooltipText"></div></td>
                                <td bgcolor = "#A5A5A5" width = "1"><img src = "../../../../../wow-com/images/layout/pixel.html" width = "1" height = "1"></td>
                          </tr>
                          <tr>
                                <td width = "1" height = "1"></td>
                                <td bgcolor = "#4F4F4F"><img src = "../../../../../wow-com/images/layout/pixel.html" width = "1" height = "2"></td>
                                <td width = "1" height = "1"></td>
                          </tr>
                        </table>
</div>


<script type="text/javascript" src="../../../../../shared/wow-com/includes-client/third-party/tooltip.js"></script>


<style type="text/css">
  .myPurple {
  color: A335EE;
  font-weight: bold;
  font-size: 9pt;
 }

   .myBlue {
  color: 0070DD;
  font-weight: bold;
  font-size: 9pt;
 }

 .myGray {
  color: c9c9c9;
  font-size: 9pt;
 }


 .myGreen {
  color: 00FF00;
  font-size: 9pt;
 }

 .myYellow {
  color: ffd517;
  font-size: 9pt;
 }

 .myRed {
  color: d80000;
  font-size: 9pt;
 }

 .myTable {
  color: FFFFFF;
  font-size: 9pt;
 }

 .reallySmall { font-size: 7pt; color: #B1B1B1;}

        .attribute                 { font-family: "Arial", "Helvetica", "Sans-Serif"; color: #000000; font-weight: bold; font-size: 12;}

              #male { position: absolute;
                        top: -90px;
                        left: -150px;
                        z-index: 100;
       }

              #maleLeft { position: absolute;
                        top: -88px;
                        left: -125px;
                        z-index: 100;
       }

              #female { position: absolute;
                        top: -115px;
                        left: 13px;
                        z-index: 100;
       }

                #wrapper { position: relative;
                        z-index: 100;
       }

</style>

<!--HEADER------------------------------------------>
<div class = "header">
<table cellpadding="0" cellspacing="0" border="0" width = "100%">
<tr>
        <td colspan = "3"><img src = "../../../../../shared/wow-com/images/layout/pixel.gif" width = "1" height = "12"></td>
</tr>
<tr>
        <td width = "29"><img src = "../../../../../shared/wow-com/images/headers/dateheader/dateheader-left.gif" width = "31" height = "38"></td>
        <td background = "../../../../../shared/wow-com/images/headers/dateheader/dateheader-bg.gif" width = "100%"><h3 class = "titleLight">Factions</h3></td>
        <td width = "17"><img src = "../../../../../shared/wow-com/images/headers/dateheader/dateheader-right.gif" width = "17" height = "38"></td>
</tr>
</table>
</div>

<!--<table cellpadding="0" cellspacing="0" border="0" width = "100%" background = "/shared/wow-com/images/basics/factions/zandalar/banner-bg.jpg">
  <tr>
    <td><div id = "wrapper"><div id = "female"><img src = "/shared/wow-com/images/basics/factions/zandalar/text.jpg" alt = "Zandalar Tribe"></div></div></td>
    <td width = "100%"><img src = "/shared/wow-com/images/layout/pixel.gif" height = "161" width = "1"></td>
  </tr>
</table>

<table cellpadding="0" cellspacing="0" border="0" width = "100%" background = "/shared/wow-com/images/banners/info/races/images/banner-bottom.jpg">
  <tr>
    <td width = "100%"><img src = "/shared/wow-com/images/layout/pixel.gif" height = "18"></td>
  </tr>
</table> -->
<!-- BEGIN OLD BANNER SHOW X--




<style type="text/css">
        .attribute                 { font-family: "Arial", "Helvetica", "Sans-Serif"; color: #000000; font-weight: bold; font-size: 12;}
              #icon { position: absolute;
                        top: -105px;
                        left: 500px;
                        z-index: 100;
       }
              #text { position: relative;
                        top: 78px;
                        left: 12px;
                        z-index: 100;
       }
                #wrapper { position: relative;
                        z-index: 100;
       }
                #wrapper99 { position: relative;
                        z-index: 99;
       }
</style>
<table cellspacing = "0" cellpadding = "0" border = "0" width = "100%" style="background: url('/shared/wow-com/images/basics/factions/thorium/banner/background.jpg');">
  <tr>
          <td>&nbsp;
          </td>
          <td>
                  <div id = "wrapper">
                        <div id = "text">
                                <img src="/shared/wow-com/images/basics/factions/thorium/banner/en/header-text.gif">
                        </div>
                </div>
          </td>
            <td><img src="/shared/wow-com/images/layout/pixel.gif" width="1" height="160"></td>
  </tr>
  <tr>
          <td colspan="3">
                  <table cellspacing = "0" cellpadding = "0" border = "0" width = "100%">
                          <tr>
                                <td background = "/shared/wow-com/images/banner/bottom.gif" width = "100%" ><img src = "/shared/wow-com/images/layout/pixel.gif" height = "18" width = "200"></td>
                          </tr>
                  </table>
          </td>
  </tr>
</table>
<!-- END OLD BANNER SHOW -->
<!-- BEGIN NEW BANNER HIDDEN Y-->




<style type="text/css">
        .attribute                 { font-family: "Arial", "Helvetica", "Sans-Serif"; color: #000000; font-weight: bold; font-size: 12;}
              #icon { position: absolute;
                        top: -105px;
                        left: 500px;
                        z-index: 100;
       }
              #text { position: relative;
                        top: 78px;
                        left: 12px;
                        z-index: 100;
       }
                #wrapper { position: relative;
                        z-index: 100;
       }
                #wrapper99 { position: relative;
                        z-index: 99;
       }
</style>
<table cellspacing = "0" cellpadding = "0" border = "0" width = "100%" style="background: url('../../../../../shared/wow-com/images/basics/factions/thorium/banner/background.jpg');">
  <tr>
          <td>&nbsp;
          </td>
          <td>
                  <div id = "wrapper">
                        <div id = "text">
                                <img src="../../../../../shared/wow-com/images/basics/factions/thorium/banner/en/header-text.gif">
                        </div>
                </div>
          </td>
            <td><img src="../../../../../shared/wow-com/images/layout/pixel.gif" width="1" height="160"></td>
  </tr>
  <tr>
          <td colspan="3">
                  <table cellspacing = "0" cellpadding = "0" border = "0" width = "100%">
                          <tr>
                                <td background = "../../../../../shared/wow-com/images/banner/bottom.gif" width = "100%" ><img src = "../../../../../shared/wow-com/images/layout/pixel.gif" height = "18" width = "200"></td>
                          </tr>
                  </table>
          </td>
  </tr>
</table>
<!-- END NEW BANNER HIDDEN -->
<!-- BEGIN OLD Subnav SHOW X--




<div class = "postContainerPlain" style=" padding:0px; margin-top:0px; margin-bottom: 4px;">
<div class = "postBody" style=" padding:5px;">
<font face="arial,helvetica" size=1><span>
<center>
<small>
[&nbsp;<a href="/en/info/basics/factions/">Faction Information</a> | <a href="/en/info/basics/reputation.html">Reputation Information</a> ]<br>
[&nbsp;<a href="/en/info/basics/factions/argent/index.html">Argent Dawn</a>:
<a href="/en/info/basics/factions/argent/vendor.html">Vendor Rewards</a> ]
[&nbsp;<a href="/en/info/basics/factions/nozdormu/index.html">Brood of Nozdormu</a> ]
[&nbsp;<a href="/en/info/basics/factions/cenarion/index.html">Cenarion Circle</a>:
<a href="/en/info/basics/factions/cenarion/rewards.html">Rewards</a> ]<br />
[&nbsp;<a href="/en/info/basics/factions/darkmoon/index.html">Darkmoon Faire</a>:
<a href="/en/info/basics/factions/darkmoon/buffs.html">Buffs</a> |
<a href="/en/info/basics/factions/darkmoon/rewards.html">Rewards</a> ] <br>
[&nbsp;<a href="/en/info/basics/factions/thorium/index.html">Thorium Brotherhood</a>:
<a href="/en/info/basics/factions/thorium/vendor.html">Vendor Rewards</a> ]
[&nbsp;<a href="/en/info/basics/factions/timbermaw/index.html">Timbermaw Hold</a>:
<a href="/en/info/basics/factions/timbermaw/rewards.html">Rewards</a> ]<br>
[&nbsp;<a href="/en/info/basics/factions/zandalar/index.html">Zandalar Tribe</a>:
<a href="/en/info/basics/factions/zandalar/quests.html">Quest Rewards</a> |
<a href="/en/info/basics/factions/zandalar/vendor.html">Vendor Rewards</a> ] <br>
[&nbsp;<a href="/en/info/basics/factions/index.html#battlegrounds">Battlegrounds Factions</a> ]
</small>
</center>
</span></font>
</div>
</div>
<!-- End OLD Subnav SHOW -->
<!-- BEGIN NEW Subnav HIDDEN Y-->
<script language = "javascript">
var pageId = "Thorium Brotherhood";
</script>


<script type="text/javascript" src="../../../../../shared/wow-com/includes-client/en/navtree.js"></script>


<script type="text/javascript" src="../../../../../shared/third-party/menu_com.js"></script>
<script type="text/javascript" src="../../../../../shared/wow-com/includes-client/navtreefunctions.js"></script>


<style type="text/css">

.navigation
                {
                font-family:arial,palatino, georgia, verdana, arial, sans-serif;
                color:#000000;
                padding:5px;
                margin-bottom: 4px;
                background-color: #E7CFA3;
                background-image: url('../../../../../shared/wow-com/images/parchment/plain/light.jpg');
                border-style: solid; border-color: #000000; border-width: 0px; border-bottom-width:1px; border-top-width:1px;
                }

.button
                {
                color:#FFFFFF;
                font-size:9px;
                letter-spacing:-1px;
                }

a.nav:link                {
                        font-family: arial,verdana, sans-serif;
                        color: CBA300;
                        font-size: 11px;
                        font-weight:normal;
                        }

a.nav:visited         {
                        font-family: arial,verdana, sans-serif;
                        color: CBA300;
                        font-size: 11px;
                        font-weight:normal;
                        }

a.nav:hover                {
                        font-family: arial,verdana, sans-serif;
                        color: FFFFFF;
                        font-size: 11px;
                        font-weight:normal;
                        }

a.nav:active         {
                        font-family: arial,verdana, sans-serif;
                        color: CBA300;
                        font-size: 11px;
                        font-weight:normal;
                        }


</style>
<div class="navigation">
<center>
<table cellspacing = "0" cellpadding = "0" border = "0" width = "96%">
<tr>

<script language = "javascript">

        var iconId;
        if (result!=1)
                document.write('<td width="59" rowspan="3" valign = "top"><a href = "' + Menu2[1] + '"><img src = "/shared/wow-com/images/subnav/icon_' + Menu2[11].toLowerCase() + '.jpg" width="59" height="65" border = "0"></a></td>');
        else
                document.write('<td width="59" rowspan="3" valign = "top"><a href = "' + Menu1[1] + '"><img src = "/shared/wow-com/images/subnav/icon_' + Menu1[11].toLowerCase() + '.jpg" width="59" height="65" border = "0"></a></td>');
</script>



<td height="15" background="../../../../../shared/wow-com/images/subnav/nav_top.jpg"></td>
<td width="18" height="65" rowspan="3" style="background-image:url(../../../../../shared/wow-com/images/subnav/nav_right.jpg); background-position:top; background-repeat:no-repeat;"></td>
</tr>

<tr>
<td height="17" background="../../../../../shared/wow-com/images/subnav/nav_middle.jpg" nowrap><div id = "filterMenu"></div></td>
</tr>

<tr>
<td>
        <table cellpadding="0" cellspacing="0" border="0">
        <tr>
        <td width="5" height="33" style="background-image:url(../../../../../shared/wow-com/images/subnav/leftsubnav.jpg); background-position:top; background-repeat:repeat-x;"><img src="../../../../../shared/wow-com/images/layout/pixel.gif" width="5" height="1"></td>
        <td height="33" background="../../../../../shared/wow-com/images/subnav/subnav.jpg" width="100%">
                <table height="33" cellpadding="0" cellspacing="0" border="0" width="100%">
                <tr>
                <td width="5" height="5" background="../../../../../shared/wow-com/images/subnav/subnav_topleft.gif"></td>
                <td height="5" background="../../../../../shared/wow-com/images/subnav/subnav_top.gif"></td>
                <td width="6" height="5" background="../../../../../shared/wow-com/images/subnav/subnav_topright.gif"></td>
                </tr>
                <tr>
                <td width="5" height="19" background="../../../../../shared/wow-com/images/subnav/subnav_left.gif"></td>
                <td height="19" style="text-align:center;" background="../../../../../shared/wow-com/images/subnav/subnav_bg.gif" valign="middle"><img src="../../../../../shared/wow-com/images/layout/pixel.gif" width="1" height="1"><small class="button" style="color:#808080; letter-spacing:normal;">

<script language = "javascript">

//printSubNav(result,1);

printSubNav2(result);

</script>


                </small></td>
                <td width="6" height="19" background="../../../../../shared/wow-com/images/subnav/subnav_right.gif"></td>
                </tr>
                <tr>
                <td width="5" height="9" background="../../../../../shared/wow-com/images/subnav/subnav_botleft.gif"></td>
                <td height="9" background="../../../../../shared/wow-com/images/subnav/subnav_bot.gif"></td>
                <td width="6" height="9" background="../../../../../shared/wow-com/images/subnav/subnav_botright.gif"></td>
                </tr>
                </table>
        </td>
        </tr>
        </table>
</td>
</tr>

</table>
</center>
</div>



<!-- END NEW Subnav HIDDEN -->

<div class = "guideHeader">
<table width="100%" align="center" cellspacing = "0" cellpadding = "0" border = "0" >
<tr>
        <td width="10"><img src="../../../../../shared/wow-com/images/headers/tabheader/tabheader-left-left.jpg" width="17" height="29" border="0" ></td>
    <td width = "362" background = "../../../../../shared/wow-com/images/headers/tabheader/tabheader-left.jpg" align = "left" NOWRAP><h3 class = "guideTitle">Thorium Brotherhood</h3></td>
        <td width="100%" background = "../../../../../shared/wow-com/images/headers/tabheader/tabheader-bg.jpg"></td>
</tr>
</table>
</div>

<div class = "postContainerplain">
<div class = "postBody">
<blockquote>

<img src = "../../../../../shared/wow-com/images/smallcaps/plain/t.gif" align = "left">he Searing Gorge is home to a group of exceptionally stout dwarves who have split from the Dark Iron clan. On the cliffs overlooking the region called the Cauldron, in the far north of the Searing Gorge, the dwarves of the Thorium Brotherhood have established a base of operations, Thorium Point. From here, they keep a close eye on the Dark Iron dwarves’ activities in the Searing Gorge and beyond. Adventurers seeking out Thorium Point will find that the dwarves of the Thorium Brotherhood hold great rewards for those who aid them in their neverending struggle against their former brethren.
<p>
The Thorium Brotherhood comprises many exceptionally talented craftsmen, and the blacksmiths of the Brotherhood are rumored to be among the finest Azeroth has ever seen. They possess the knowledge required to make the arms and armaments of Ragnaros, the Fire Lord, but lack the manpower to obtain the materials required for the crafting. It is rumored that one member of the Thorium Brotherhood has been empowered to trade the dwarves’ fabled recipes and plans with those who can prove their loyalty to the Brotherhood. Of course, proving one’s loyalty at some point may include venturing to the heart of the Molten Core, the domain of Ragnaros, the Fire Lord himself, to supply the dwarves with the rare raw materials found there. A daunting task, no doubt, but gaining access to the Thorium Brotherhood’s secrets should prove to be a reward well worth the effort.

</blockquote>
<p>
<br>


<br>

<CENTER>[<a href="../../../../index.php">Return to Main</a>]</CENTER>
<br>
<!---------------------------END MAIN------------------------------>

</div>
</div>



<!--Related Links-->
<div class = "guideHeader">
<table width="100%" align="center" cellspacing = "0" cellpadding = "0" border = "0" >
<tr>
        <td width="10"><img src="../../../../../shared/wow-com/images/headers/tabheader/tabheader-left-left.jpg" width="17" height="29" border="0" ></td>
    <td width = "362" background = "../../../../../shared/wow-com/images/headers/tabheader/tabheader-left.jpg" align = "left" NOWRAP><h3 class = "guideTitle">Related Links</h3></td>
        <td width="100%" background = "../../../../../shared/wow-com/images/headers/tabheader/tabheader-bg.jpg"></td>
</tr>
</table>
</div>

<div class = "postContainerPlain">
<div class = "postBody">
<script language = "javascript">
printSubNav(result,2)
printRelatedLinks(result);
</script>
</div>
</div>
<!--End Related Links-->


</td>
</tr>
</table>
</div>
</center>
</div>
<div id="pageEnd"></div>



</body> </html>


<script language="JavaScript">
<!--
var SymRealOnLoad;
var SymRealOnUnload;

function SymOnUnload()
{
  window.open = SymWinOpen;
  if(SymRealOnUnload != null)
     SymRealOnUnload();
}

function SymOnLoad()
{
  if(SymRealOnLoad != null)
     SymRealOnLoad();
  window.open = SymRealWinOpen;
  SymRealOnUnload = window.onunload;
  window.onunload = SymOnUnload;
}

SymRealOnLoad = window.onload;
window.onload = SymOnLoad;

//-->
</script>
<? include $Offset."bottem.php"; ?>