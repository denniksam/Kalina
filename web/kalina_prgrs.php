<?php
// $teta_1 = 0x8000000000000000;
// $hi_bit_1 = ($teta_1 & 0x8000000000000000)?1:0;
// echo $teta_1,'<br>';
// echo hexdec($teta_1),'<br>';
// echo $hi_bit_1;
// exit;

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
require_once "kalina_funcs.php";
/*
echo pi_0(0x23),' ',dechex(pi_0(0x23)),'<br>';
echo pi_1(0x23),' ',dechex(pi_1(0x23)),'<br>';
echo pi_2(0x23),' ',dechex(pi_2(0x23)),'<br>';
echo pi_3(0x23),' ',dechex(pi_3(0x23)),'<br>';
echo _1_pi_0(0x23),' ',dechex(_1_pi_0(0x23)),'<br>';
echo _1_pi_1(0x23),' ',dechex(_1_pi_1(0x23)),'<br>';
echo _1_pi_2(0x23),' ',dechex(_1_pi_2(0x23)),'<br>';
echo _1_pi_3(0x23),' ',dechex(_1_pi_3(0x23)),'<br>';
*/
$G = array(
    array(),
    array()
);

$K = array(
    array(0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07),
    array(0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F)
);

$K_s = array(
    array(0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00),
    array(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
);
show($K,"Key");
$K_s = eta($K_s,$K);
show($K_s,"eta");
$K_s = pee($K_s);
show($K_s,"pi ");
$K_s = tau($K_s);
show($K_s,"tau");
$K_s = psi($K_s);
show($K_s,"psi");
$K_s = kappa($K_s,$K);
show($K_s,"kappa");

echo '<br/>';

$K_s = pee($K_s);
show($K_s,"pi ");
$K_s = tau($K_s);
show($K_s,"tau");
$K_s = psi($K_s);
show($K_s,"psi");

echo '<br/>';

$K_s = eta($K_s,$K);
show($K_s,"eta");
$K_s = pee($K_s);
show($K_s,"pi ");
$K_s = tau($K_s);
show($K_s,"tau");
$K_s = psi($K_s);
show($K_s,"psi---");

$KT = $K_s;// Intermediate key  
echo '<br>';
/*
 //step-by-step show mode
$K0 = fi($KT,8);  
show($K0,"fi");  
$K0 = eta($K0,$K);    // *
show($K0,"eta");
$K0 = pee($K0);    
show($K0,"pi");
$K0 = tau($K0);
show($K0,"tau");
$K0 = psi($K0);
show($K0,"psi");
$K0 = kappa($K0,fi($KT,8));// **
show($K0,"kappa");
$K0 = pee($K0);    
show($K0,"pi");
$K0 = tau($K0);
show($K0,"tau");
$K0 = psi($K0);
show($K0,"psi");//До сюда все правильно
$K0 = eta($K0,fi($KT,8));//А это не совпадает????? Хотя то же, что и на * и на **
show($K0,"eta");
*/
$K_0 = psi(tau(pee(kappa(fi($KT,8),psi(tau(pee(eta(fi($KT,8),$K)))))))); 
show($K_0,"0-");
$K_0 = eta(fi($KT,8),$K_0);
show($K_0,"0-");

$teta = array(
        array(0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01),
        array(0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01)
    );
/*$K0 = eta($K0,$teta);
show($K0,"teta");

for($i=0;$i<80;$i+=4)
    show(shl($K,$i),$i);
*/
echo "<hr><br>";
$K_2 = psi(tau(pee(kappa(fi($KT,9),psi(tau(pee(eta(fi($KT,9),ror($K,32*2))))))))); 
show($K_2,"2-");
$K_2 = eta(fi($KT,9),$K_2);
show($K_2,"2-");

show(shl($teta,9),"teta");
$K2 = ror($K,32*2);
show($K2,"K2");
show(fi($KT,9),"fi");
$K2 = eta(fi($KT,9),$K2);
show($K2,"eta-fi");

$K2 = pee($K2);    
show($K2,"pi");
$K2 = tau($K2);
show($K2,"tau");
$K2 = psi($K2);
show($K2,"psi");

$K2 = kappa($K2,fi($KT,9));
show($K2,"kappa");
$K2 = pee($K2);    
show($K2,"pi");
$K2 = tau($K2);
show($K2,"tau");
$K2 = psi($K2);
show($K2,"psi");
$K2 = eta($K2,fi($KT,9));
show($K2,"eta");

    
echo "</div></body></html>";