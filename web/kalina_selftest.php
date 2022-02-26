<?php
require "kalina.php";

$selftest = array();
$selftest[] = array('blocksize'=>128,'keysize'=>128,'mode'=>'encrypt',
					'block'=>'101112131415161718191A1B1C1D1E1F',
					'key'=>'000102030405060708090A0B0C0D0E0F',
					'result'=>'81BF1C7D779BAC20E1C9EA39B4D2AD06');
                    
$selftest[] = array('blocksize'=>128,'keysize'=>128,'mode'=>'decrypt',
					'block'=>'1F1E1D1C1B1A19181716151413121110',
					'key'=>'0F0E0D0C0B0A09080706050403020100',
					'result'=>'7291EF2B470CC7846F09C2303973DAD7');
                                        
$selftest[] = array('blocksize'=>128,'keysize'=>256,'mode'=>'encrypt',
					'block'=>'202122232425262728292A2B2C2D2E2F',
					'key'=>'000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F',
					'result'=>'58EC3E091000158A1148F7166F334F14');
                                        
$selftest[] = array('blocksize'=>128,'keysize'=>256,'mode'=>'decrypt',
					'block'=>'2F2E2D2C2B2A29282726252423222120',
					'key'=>'1F1E1D1C1B1A191817161514131211100F0E0D0C0B0A09080706050403020100',
					'result'=>'F36DB456CEFDDFE1B45B5F7030CAD996');
                                                            
$selftest[] = array('blocksize'=>256,'keysize'=>256,'mode'=>'encrypt',
					'block'=>'202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F',
					'key'=>'000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F',
					'result'=>'F66E3D570EC92135AEDAE323DCBD2A8CA03963EC206A0D5A88385C24617FD92C');
                                        
$selftest[] = array('blocksize'=>256,'keysize'=>256,'mode'=>'decrypt',
					'block'=>'3F3E3D3C3B3A393837363534333231302F2E2D2C2B2A29282726252423222120',
					'key'=>'1F1E1D1C1B1A191817161514131211100F0E0D0C0B0A09080706050403020100',
					'result'=>'7FC5237896674E8603C1E9B03F8B4BA3AB5B7C592C3FC3D361EDD12586B20FE3');

$selftest[] = array('blocksize'=>256,'keysize'=>512,'mode'=>'encrypt',
					'block'=>'404142434445464748494A4B4C4D4E4F505152535455565758595A5B5C5D5E5F',
					'key'=>'000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F',
					'result'=>'606990E9E6B7B67A4BD6D893D72268B78E02C83C3CD7E102FD2E74A8FDFE5DD9');
                                        
$selftest[] = array('blocksize'=>256,'keysize'=>512,'mode'=>'decrypt',
					'block'=>'5F5E5D5C5B5A595857565554535251504F4E4D4C4B4A49484746454443424140',
					'key'=>'3F3E3D3C3B3A393837363534333231302F2E2D2C2B2A292827262524232221201F1E1D1C1B1A191817161514131211100F0E0D0C0B0A09080706050403020100',
					'result'=>'18317A2767DAD482BCCD07B9A1788D075E7098189E5F84972D0B916D79BA6AE0');
                    
$selftest[] = array('blocksize'=>512,'keysize'=>512,'mode'=>'encrypt',
					'block'=>'404142434445464748494A4B4C4D4E4F505152535455565758595A5B5C5D5E5F606162636465666768696A6B6C6D6E6F707172737475767778797A7B7C7D7E7F',
					'key'=>'000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F',
					'result'=>'4A26E31B811C356AA61DD6CA0596231A67BA8354AA47F3A13E1DEEC320EB56B895D0F417175BAB662FD6F134BB15C86CCB906A26856EFEB7C5BC6472940DD9D9');
                                        
$selftest[] = array('blocksize'=>512,'keysize'=>512,'mode'=>'decrypt',
					'block'=>'7F7E7D7C7B7A797877767574737271706F6E6D6C6B6A696867666564636261605F5E5D5C5B5A595857565554535251504F4E4D4C4B4A49484746454443424140',
					'key'=>'3F3E3D3C3B3A393837363534333231302F2E2D2C2B2A292827262524232221201F1E1D1C1B1A191817161514131211100F0E0D0C0B0A09080706050403020100',
					'result'=>'CE80843325A052521BEAD714E6A9D829FD381E0EE9A845BD92044554D9FA46A3757FEFDB853BB1F297FF9D833B75E66AAF4157ABB5291BDCF094BB13AA5AFF22');

                    
echo <<< TXT
<html>
<head>
<meta charset="utf8">
<style>
body{font-family:"Courier New", Courier, monospace;}
</style>
</head>
<body>
TXT;
/*$b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";
for($i=0;$i<strlen($b64);$i++)
echo "'",$b64[$i],"'",'=>',$i,',';
$TS_ind=array('A'=>0,'B'=>1,'C'=>2,'D'=>3,'E'=>4,'F'=>5,'G'=>6,'H'=>7,'I'=>8,'J'=>9,'K'=>10,'L'=>11,'M'=>12,'N'=>13,'O'=>14,'P'=>15,'Q'=>16,'R'=>17,'S'=>18,'T'=>19,'U'=>20,'V'=>21,'W'=>22,'X'=>23,'Y'=>24,'Z'=>25,'a'=>26,'b'=>27,'c'=>28,'d'=>29,'e'=>30,'f'=>31,'g'=>32,'h'=>33,'i'=>34,'j'=>35,'k'=>36,'l'=>37,'m'=>38,'n'=>39,'o'=>40,'p'=>41,'q'=>42,'r'=>43,'s'=>44,'t'=>45,'u'=>46,'v'=>47,'w'=>48,'x'=>49,'y'=>50,'z'=>51,'0'=>52,'1'=>53,'2'=>54,'3'=>55,'4'=>56,'5'=>57,'6'=>58,'7'=>59,'8'=>60,'9'=>61,'-'=>62,'_'=>63);
echo $TS_ind[1],' ',$TS_ind['1'];
exit;*/
function ordUTF8($c) {
    $offset = 0;
    $code = ord($c[$offset]); 
    if ($code >= 128) {        //otherwise 0xxxxxxx
        if ($code < 224) $bytesnumber = 2;                //110xxxxx
        else if ($code < 240) $bytesnumber = 3;        //1110xxxx
        else if ($code < 248) $bytesnumber = 4;    //11110xxx
        $codetemp = $code - 192 - ($bytesnumber > 2 ? 32 : 0) - ($bytesnumber > 3 ? 16 : 0);
        for ($i = 2; $i <= $bytesnumber; $i++) {
            $offset ++;
            $code2 = ord($c[$offset]) - 128;        //10xxxxxx
            $codetemp = $codetemp*64 + $code2;
        }
        $code = $codetemp;
    }
    return $code;
}
/*$c = "ї";//"Особливої важливості";
for($i=0;$i<strlen($c);$i++)
    echo $i,' ',ord($c[$i]),'<br/>';

echo chr(227),chr(149),chr(149),' ';exit;
$c = 'ї';
echo $c,' ',strlen($c),' ',ordUTF8($c),'<br/>';
for($i=0;$i<strlen($c);$i++)
    echo ord($c[$i]),' ';
echo '<br/>';
for($i=0;$i<strlen($c);$i++)
    echo chr(ord($c[$i]));
exit;
$str = "";
for($i=128;$i<256;$i++)
    $str.= $i+' '+chr($i)+'<br/>';
echo $str;
exit;*/

/*
foreach($selftest as $tst){
    $k = new Kalina($tst['blocksize'],$tst['keysize']);
    $k->setKeyHex($tst['key']);
    $res = ($tst['mode']=='encrypt')?$k->encryptHex($tst['block']):$k->decryptHex($tst['block']);
    echo $tst['blocksize'],' ',$tst['keysize'],' ',$tst['mode'],' - ',($res == $tst['result'])?"<span style='color:green;font-weight:bold'>Passed</span>":"<span style='color:red;font-weight:bold'>Failed</span>",'<br/>',$res,'<br/>',$tst['result'],'<br/>','<br/>';
}
*/
$k = new Kalina(256,512);
$k->setKeyHex("000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F");
// $k->setKeyHex("3F3E3D3C3B3A393837363534333231302F2E2D2C2B2A292827262524232221201F1E1D1C1B1A191817161514131211100F0E0D0C0B0A09080706050403020100");

$str=<<<STR
<div style="width:300px;border:1px solid red;background-color:#ffeeee;">
	<table border='1' cellspacing='0' style="margin:20px;">
	<tr><th>Таємний параметр</th><th>Значення</th></tr>
	<tr><td>3</td><td>Таємно</td></tr>
	<tr><td>2</td><td>Цілком таємно</td></tr>
	<tr><td>1</td><td>Особливої важливості</td></tr>
	</table>
</div>
STR;
$str='<div style="width:300px;border:1px solid red;background-color:#ffeeee;"><table border="1" cellspacing="0" style="margin:20px;"><tr><th>Таємний параметр</th><th>Значення</th></tr><tr><td>3</td><td>Таємно</td></tr><tr><td>2</td><td>Цілком таємно</td></tr><tr><td>1</td><td>Особливої важливості</td></tr>	</table></div>';//"Особливої - важливості";
$str='Таємне повідомлення $100';
$c = $k->encryptStr($str);
echo $c,'<hr/><br/>';
$t = $k->transportEncode($c);
echo $t,'<hr/><br/>';
/*$Be = base64_encode($c);
echo $Be,'<hr/><br/>';*/
$T = $k->transportDecode($t);
echo $T,'<hr/><br/>';
/*$Bd = base64_decode($Be);
echo $Bd,'<hr/><br/>';
for($i=0;$i<strlen($T);$i++)
    echo $i,' ',$c[$i],' ',ord($c[$i]),' ',$T[$i],' ',ord($T[$i]),' ',($c[$i]==$T[$i])?'+':'<b>NO</b>','<br>';

echo strlen($c),' ',strlen($T),' ',strlen($Bd),' ', ($c==$T)?'+':'-','<br>';
*/
$d = $k->decryptStr($T);
echo $d,'<hr/><br/>';
