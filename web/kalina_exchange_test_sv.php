<html>
<head>
<meta charset="utf8">
<style>
body{font-family:"Courier New", Courier, monospace;}
</style>
</head>
<body>
<?php
if(isset($_GET['hid'])){
    include "kalina.php";
    $k = new Kalina(256,512);
    $k->setKeyHex("000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F");
    $t = $k->transportDecode($_GET['hid']);
    echo $k->decryptStr($t),'<hr><br>';
}
if(isset($_GET['txt'])){
    include_once "kalina.php";
    $k = new Kalina(256,512);
    $k->setKeyHex("000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F");
    echo "txt: ",$_GET['txt'],'<hr><br>';
    $c = $k->encryptStr($_GET['txt']);
    echo "state2string: ",$k->state2string(),'<hr><br>';
    
    $e = $k->transportEncode($c);
    echo "transportEncode: ",$e,'<hr><br>';
    $t = $k->transportDecode($e);
    echo "decrypt: ",$k->decryptStr($t),'<hr><br>';
}
?>
<form id="f1" method="GET" action="kalina_exchange_test.php">
    Введіть дані: <input type="text" name="txt" id="t1"/>
    <input type="hidden" name="hid" id="hd1"/>
</form>
    <br/>
    Автозаповнення: <textarea name="def" id="t2" rows="4" cols="50"> а, б, в, г, ґ, д, е, є, ж, з, и, і, ї, й, к, л, м, н, о, п, р, с, т, у, ф, х, ц, ч, ш, щ, ь, ю, я"</textarea>
    <br/>
    <input type="button" name="send" value="Надіслати" onclick="ssend()"/>
    <input type="button"  value="Отримати" onclick="sget()"/>
    <input type="button"  value="Скинути" onclick="window.location.search = '';"/>
<div id="d1" style="border:1px solid blue;height:300px;width:500px;"></div>
<script src="kalina.js"></script>
<script>
function ssend(){
    var k = new Kalina(256,512);
    k.setKeyHex("000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F");
    var t = window.t2.value;
    var e = k.encryptStr(t);
    var t = k.transportEncode(e);
    window.hd1.value = t;
    window.f1.submit();
}
function sget(){
    var x = new XMLHttpRequest();
    if(x){
        x.open('GET','kalina_ajax_test.php',true);
        x.onreadystatechange=function(){
            if(x.readyState == 4) 
			if(x.status == 200){
                var k = new Kalina(256,512);
                k.setKeyHex("000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F202122232425262728292A2B2C2D2E2F303132333435363738393A3B3C3D3E3F");
                /*var s = k.transportEncode(k.encryptStr('Таємне повідомлення $100'));
                window.d1.innerHTML = s+'<hr><br>';*/
                var t = x.responseText;
                window.d1.innerHTML += 'Одержано:<br>'+t+'<hr><br>';
                /*var D = k.transportDecode(s);
                window.d1.innerHTML += D+'<hr><br>';*/
                var d = k.transportDecode(t);
                /*window.d1.innerHTML += d+'<hr><br>';
                var E = k.decryptStr(D);   
                window.d1.innerHTML += E+'<hr><br>';*/
                var e = k.decryptStr(d);   
                window.d1.innerHTML += 'Декодовано:<br>'+e+'<hr><br>';
            }
        }
        x.send();
    }
    
}
</script>
</body>
</html>