<?php
require_once "kalina_funcs.php";
function bitWeight($x)
{
	$x = (($x >> 1) & 0x55) + ($x & 0x55);
	$x = (($x >> 2) & 0x33) + ($x & 0x33);
	$x = (($x >> 4) & 0x0F) + ($x & 0x0F);
	return $x;
}
function inc(&$G)
{
    $c = 2;
    $carry_over = 1;
    for($j=$c-1;$j>=0 && $carry_over==1;$j--)
        for($i=7;$i>=0 && $carry_over==1;$i--){
            $G[$j][$i] = ($G[$j][$i]+1)&0xFF;
            $carry_over = ($G[$j][$i] == 0)? 1 : 0;
        }
}

$K = array(
    array(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF),
    array(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF)
);

echo <<< TXT
<html>
<head>
<meta charset="utf8">
<style>
body{font-family:"Courier New", Courier, monospace;}
</style>
</head>
<body>
<div style="height:10000px;">
TXT;
show($K);
inc($K);
show($K);
echo "</div></body></html>";