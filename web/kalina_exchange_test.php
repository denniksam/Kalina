<html>
<head>
<meta charset="utf8">
<style>
    body{font-family:"Courier New", Courier, monospace;}
    .fileinput-droppable {border: 1px solid blue;}
    .fileinput-not-droppable {border: 1px solid golg;}
    #key-text{display:inline-block;height:35px;padding-top:15px;vertical-align:top;width:150px;}
    #key-box{display:inline-block;height:50px;position:relative;width:300px;vertical-align:top;}
    #key-input{display:block;position:absolute;left:0;top:0;width:300px;height:50px;z-index:1;opacity:0;filter:alpha(opacity=0);}
    #key-face{display:block;height:42px;position:absolute;left:0;top:0;width:300px;z-index:0;text-align:center;padding-top:8px;}
    #data-text{display:inline-block;margin-top:15px;width:150px;}
    #data-input{border:1px solid green;padding-left:3px;width:302px;}
    #log{border-top:1px solid blue;/*border:1px solid blue;height:200px;width:450px;*/margin-top:20px;}
    #xchng-text{display:inline-block;margin-top:15px;width:150px;}
    #xchng-btn{}
</style>
</head>
<body>
    <div id="key-text">Введення ключа:</div><div id="key-box"><input id="key-input" type="file"/><div id="key-face"></div></div><div id="file-content"></div>
    <div id="data-text">Введення даних: </div><input id="data-input" type="text" value="Цілком таємно"/><br/>
    <div id="xchng-text">Обмін даними: </div><input type="button" id="xchng-btn" value="Надіслати" onclick="ssend()"/><br/>
    
    <div id="log"></div>
<script src="kalina.js"></script>
<script>
var K,k=0;
K = new Kalina(256,512);
!function canDnD() {
  var iface = document.getElementById('key-face');
  var div = document.createElement('div');
  if( (('draggable' in div) || ('ondragstart' in div && 'ondrop' in iface)) && 'FormData' in window && 'FileReader' in window)
  {
    iface.classList.add('fileinput-droppable');
    iface.innerHTML = 'Натисніть для відкриття файлу<br/>або перетягніть файл сюди';
  }
  else{
    iface.classList.add('fileinput-droppable');
    iface.innerHTML = 'Натисніть для <br/>відкриття файлу';
  }
}();

function readKey(e) {
  var file = e.target.files[0];
  if (!file) {
    return;
  }
  var reader = new FileReader();
  reader.onload = function(e) {
    var fname = file;
    var contents = e.target.result;
    var l = document.getElementById('log');
    var iface = document.getElementById('key-face');
    var stts = "",clr="green"; 
    iface.innerHTML = file.name;  
    try{K.setKeyHex(contents);k=1;l.innerHTML+= "Встановлено ключ: "+contents+"<br/>";}
    catch(err){stts=" не";clr="red";l.innerHTML+= "Помилка читання ключа<br/>";k=0;return false;}
    finally{iface.innerHTML += "<br><span style='color:"+clr+"'>Ключ"+stts+" прийнято</span>";}
    return true;
  };
  reader.readAsText(file);
}

document.getElementById('key-input')
  .addEventListener('change', readKey, false);

function ssend(){
    var v,e,t,a,d=document.getElementById("data-input");
    v = d.value;
    if(!k){
        var a=confirm("Ключ не встановлено. Передавати у відкритому вигляді?");
        if(!a)return false;
        e = t = v;
    }else{
        e = K.encryptStr(v);
        t = K.transportEncode(e);
    }
    
    window.log.innerHTML+="Введено: "+v+"<br/>Кодовано: "+t;

    var x = new XMLHttpRequest();
    if(x){
        x.open('GET','kalina_ajax_test.php?snt='+t+'&k='+k,true);
        x.onreadystatechange=function(){
            if(x.readyState == 4) 
			if(x.status == 200){
                
                var r=x.responseText.split('~BlSEP~'),d,e;
                if(r[1]===undefined||r[2]===undefined){window.log.innerHTML += "<br/>Помилка: неповна відповідь сервера<br/>"+x.responseText;return false;}
                window.log.innerHTML += '<br/>Декодовано сервером:'+r[0]+'<br>Прийнято: '+r[1]+'<br>';
                if(r[2]==1){
                    try{d = K.transportDecode(r[1]);e = K.decryptStr(d);}
                    catch(ex){window.log.innerHTML += 'Помилка декодування відповіді сервера '+ex+'<br>';return false;}
                    window.log.innerHTML += 'Декодовано:'+e+'<br>';
                    return true;
                }
                
            }
        }
        x.send();
    }
    
}
</script>
</body>
</html>