<link href="skin/wrath/wrath.css" type="text/css" rel="stylesheet" />
<script type="text/javascript" src="js/menu.js"></script>
<script type="text/javascript" src="skin/wrath/js/wrath.js"></script>
<table class="main_body" cellspacing="0" cellpadding="0"><tbody>
<tr>
<!-- TOP MENU -->
 <td class="top_menu" colspan="3">
   <a id="langmenu_0" onmouseover="dd_Select(this);" onmouseout="dd_Unselect(this);" style="cursor:pointer;"><?php echo $lang['lang']; ?></a>&nbsp;&nbsp;*&nbsp;&nbsp;
 </td>
</tr>
<tr class="skin_top">
 <td class="skin_topleft"></td>
 <td class="skin_topcenter">
  <div style="position: relative;">
   <div class="skin_topcenter"></div>
   <div class="skin_topleft"></div>
   <div class="skin_topright"></div>
   <div class="skin_topleftimg"></div>

   <div class="skin_searchmenu">
    <table class="search">
     <tr>
      <td class="sleft"></td>
      <td>
       <form method="get" action="" style="display: inline;">
        <input name="s" type="hidden" value="all">
        <input class="ls_search" alt="all" name="name" id="topsearch">
       </form>
      </td>
      <td>
       <select onchange="changeSearch(this);">
        <option value="site">All</option>
        <option value="item">Item</option>
        <option value="itemset">Item Set</option>
        <option value="quest">Quest</option>
        <option value="spell">Spell</option>
        <option value="npc">Npc</option>
        <option value="object">Object</option>
        <option value="faction">Faction</option>
        <option value="area">Area</option>
        <option value="player">Player</option>
       </select>
      </td>
      <td><a class="searhButton" href="#" onclick="searchClick(this);"></a></td>
      <td class="sright"></td>
     </tr>
    </table>
   </div>
  </div>

 </td>
 <td class="skin_topright"></td>
</tr>
<tr>
 <td class="skin_left">
  <div style="position: relative;">
   <div class="skin_leftimg1"></div>
   <div class="skin_leftimg2"></div>
<!--
 Left menu here
-->
   <div class="skin_leftmenu" id="leftmenu" align="right">
<?php
   $left_menu_file = "left_menu_".$config['lang'].".js";
   include_once("include/simple_cacher.php");
   if (checkUseCacheJs($left_menu_file, 60*60*24))
   {
     include("site_menu.php");
     echo 'var leftmenu = '.php2js($menu).';';
     echo 'generateLeftMenu("leftmenu");';
     flushJsCache($left_menu_file);
   }
?>
   </div>
<!--
 Left menu end
-->

 </td>
 <td class="skin_center">
 <table class="body" cellspacing="0" cellpadding="0">
 <tbody>
 <tr>
  <td class="bodyleft"></td>
  <td class="bodycenter" align="center"><?php include("main.php");?></td>
  <td class="bodyright"></td>
 </tr>
 <tr>
  <td class="bodybottom" colspan="3">
   <div style="position: relative; height: 73;">
    <div class="blimg"></div>
    <div class="brimg"></div>
   </div>
  </td>
 </tr>
 </tbody></table>
 </td>
 <td class="skin_right">
  <div style="position: relative;">
   <div class="rightimg"></div>
   <div class="rightmenu">
<!--
 Left menu here
-->
   </div>

  </div>
 </td>
</tr>
<tr><td class="skin_bottom" colspan="3"></td></tr>
<!--
 Delete all the A href="http 's this is for developers server and ect
-->
<A href="http://127.0.0.1"><font color=white>Home</font></A><br>
<A href="http://127.0.0.1/I_wow/I_cswowd/talents/index.php"><font color=white>Talent Calculator </font></A><br>
<A href="http://127.0.0.1/I_wow/I_cswowd/en/atlas/flashmap/index.html"><font color=white>The Atlas</font></A><br>
 <A href="http://127.0.0.1/I_wow/I_cswowd/Maps/interactive.php"><font color=white>Maps (Alliance & Horde) </font></A><br>
<a href="http://127.0.0.1/I_wow/I_cswowd/mini/top100.php"> <font color=white>
Top100</font></A><br/>
<A href="http://127.0.0.1/I_wow/I_cswowd/en/worldmap2/index.html"><font color=white>WorldMap 2 </font></A><br>
<a href="http://127.0.0.1/I_wow/I_cswowd/mini"> <font color=white>MiniManager</font></A><br />
<a href="http://127.0.0.1/I_wow/I_cswowd/basics/en/info/basics/index.php"> <font color=white>
The Basics-GameGuide(Little outdated - Great Newbie Guide)</font></A><br />
<A href="http://127.0.0.1/I_wow/I_cswowd/pvpmini/shared/wow-com/images/pvpminisite/en/index.php"><font color=white>PvP MiniSite </font></A><br>

<a href="http://127.0.0.1/I_wow/I_cswowd/pbreadme.html"> <font color=white>PlayerBot ReadMe</font></A><br />
</tbody>
</table>