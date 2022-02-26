<?php
if(empty($_GET['snt'])||!isset($_GET['k'])){
    echo "Not full data";
    exit;
}
if(trim($_GET['k'])=='0'){
    echo $_GET['snt'],'~BlSEP~Відкритий режим нічого секретного~BlSEP~0';
    exit;
}
require "Kalina.php";
$k = new Kalina(256,512);
$key = @file_get_contents("kalina_key1.txt");
try{$k->setKeyHex($key);$d=$k->transportDecode(trim($_GET['snt']));$de=$k->decryptStr($d);}
catch(Exception $ex){ echo 'Помилка оброблення даних '.$ex->getMessage(),'~BlSEP~Відповідь не надсилається~BlSEP~0';exit;}

$data = 'Таємне повідомлення $100';
echo $de,'~BlSEP~',$k->transportEncode($k->encryptStr($data)),'~BlSEP~1';