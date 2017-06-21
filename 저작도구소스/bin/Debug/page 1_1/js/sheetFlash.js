
//insert first.
function addJavaScriptHead(jsname) 
{
	var head = document.head;
	var s = document.createElement('script');
	s.setAttribute('type','text/javascript');
	s.setAttribute('src',jsname);
	head.appendChild(s);
}
//addJavaScriptHead('./js/jsonData.js');



//global variable
var imagePath = "./images/common/";
var mediaPath = "./media/";
var subtitlePath = "./subtitle/";
var playEffectSrc = mediaPath + "playerButton_1.mp3";
var flashInstanceCount = 0;



if(typeof initProperties == 'undefined')
{
	alert("data파일이 없습니다. data파일을 찾아 넣으세요.");
}

var jsonObj = JSON.parse(initProperties);

//beats = jsonObj["beats"];
//startTime = jsonObj["startTime"];
//endTime = jsonObj["endTime"];
//beatCounter = jsonObj["beatCounter"];
//songCounter = jsonObj["songCounter"];
//subtitleText = jsonObj["subtitleText"];

/* class: SheetFlash */
function SheetFlash(dataObj, isImageFlash, className)
{
	var curObj = this;
	//required
	this.id = flashInstanceCount++;
	this.beats 			= 	(function(obj){
								var ret = new Array();
								var chars = $(obj.split(',')).each(function(){
									ret.push(parseFloat(this));
								});  
								return ret;
							})(dataObj[0]["Value"]);
	this.startTime 		= parseFloat(dataObj[2]["Value"]);
	this.endTime 		= parseFloat(dataObj[3]["Value"]);
	this.beatCounter 	= parseInt(dataObj[6]["Value"]);
	this.songCounter 	= parseInt(dataObj[4]["Value"]);
	this.subtitleText 	= dataObj[1]["Value"];
	this.groupCounter	= parseInt(dataObj[5]["Value"]);
	
	if(typeof flashPaper == "object")
	{
		$('.sheetFlashPaper').html(flashPaper[this.id]);
	}
	
	//this.beats = jsonObj["beats"];
	//this.startTime = jsonObj["startTime"];
	//this.endTime = jsonObj["endTime"];
	//this.beatCounter = jsonObj["beatCounter"];
	//this.songCounter = jsonObj["songCounter"];
	//this.subtitleText = jsonObj["subtitleText"];
	//this.groupCounter = $(this.className + '.subtitle_group').length;
	this.isImageFlash 	= isImageFlash;
	
	//optoinal
	if(typeof className == 'String' && className.length > 1)
	{
		this.className = '.' + className + ' ';
	}
	
	//태그들을 생성한 후에 이벤트를 추가한다.
	this.createSheetFlashPlayer();
	this.eventSetting();
	
	//실행할 함수
	
	return{
		//public member function
		setScale : function(scale){
			curObj.setScale(curObj.className + '.videoPlayBar', scale);
		},
		changeSource : function(src){
			curObj.changeSource(src);
			//curObj.audioObj.setAudioSpeed(curObj.playSpeed);
			//curObj.audioObj.setAudioVolume(curObj.volume);
		},
		//true: +, false: -
		setSpeed : function(updown){
			curObj.playSpeed += (updown ? 0.5 : -0.5);
			curObj.audioObj.setAudioSpeed(curObj.playSpeed);
		},
		//true: +, false: -
		setVolume : function(updown){
			curObj.volume += (updown ? 0.1 : -0.1);
			curObj.audioObj.setAudioVolume(curObj.volume);
		},
		changeSubtitleText : function(newSubtitleText){
			curObj.resetSubtitle(newSubtitleText);
		}

	}
	
}

//set prototype property
//prototype variable
SheetFlash.prototype.className = ".sheetFlashPaper ";
SheetFlash.prototype.audioSrc = "./media/audio_1.mp3";
SheetFlash.prototype.audioSrc_mr = "./media/audio_1_mr.mp3";
SheetFlash.prototype.scale = 1.0;

//prototype function
SheetFlash.prototype.createSheetFlashPlayer = function()
{
	this.createPlayButtonForSheet();
	
	this.createAudioPanel(this.audioSrc);
	
	$(this).trigger('createEvent');
	
	
	
	if(!this.init())
	{
		console.log('초기화 실패');
		return;
	}
	
};

SheetFlash.prototype.init = function()
{
	var ret = true;
	
	//init flash variable
	this.perBeat = (this.endTime - this.startTime) / this.beatCounter;
	this.playSpeed = 1.0;
	this.audioObj.setAudioVolume(this.volume = 0.5);
	
	//init subtitle tag
	ret &= this.initSubtitle();
	//ret &= this.initPlayInfo(0, this.startTime);
	
	$(this).trigger('initEvent');
	
	return ret;
}

SheetFlash.prototype.changeSource = function(src)
{
	this.playSpeed = 1.0;
	this.volume = 0.5;
	this.audioObj.changeSource(src);
}

SheetFlash.prototype.createPlayButtonForSheet = function()
{
	//mainBoard 추가
	var playBar = $(this.className + '.videoPlayBar');
	if(playBar.length < 1){
		console.log("videoPlayBar클래스를 추가하세요.");
		return;
	}
	
	//scale관리 : 기존 크기로 고정. 스케일 변경 원할 시, setScale함수 사용
	//this.scale = playBar.width() / 970;
	playBar.width(970);
	playBar.height(88);
	
	//partNumButton 추가
	playBar.append("<div class='buttonBox'></div>");
	var partButtonBox = $(this.className + '.buttonBox');
	for(var i = 1; i <= this.groupCounter; i++)
	{
		var str = "<div class='partNumButton partNum_" + i + "'></div>";
		partButtonBox.append(str);
	}
	
	//bar 추가
	playBar.append("<div class='box'></div>");
	var box = $(this.className + '.box');
	box.append("<div class='bar'></div>");
	var bar = $(this.className + '.bar');
	bar.append("<div class='progressBar'></div>");
	bar.append("<div class='bar_rightPoint'></div>");
	$(this.className + '.bar_rightPoint').css('position', 'absolute');
	$(this.className + '.bar_rightPoint').css('left', bar.width());
	
	//button 추가
	box.append("<div class='type1Button playButton'></div>");
	box.append("<div class='type1Button pauseButton'></div>");
	box.append("<div class='type1Button stopButton'></div>");
	box.append("<div class='type1Button muteButton'></div>");
	box.append("<div class='type2Button arButton  '></div>");
	box.append("<div class='type2Button mrButton  '></div>");
	box.append("<div class='type1Button normalTone'></div>");
	
}

SheetFlash.prototype.createAudioPanel = function(audioSrcName)
{
	$(this.className + '.videoPlayBar').append("<audio class='audioPanel'><source class='audioSrc' type='audio/mpeg'/></audio>" );
	$( this.className + ".progressBar" ).css('width', "0%");
	
	//오디오 객체 생성
	this.audioObj = new SheetFlashAudio(this.className, audioSrcName);
	
}

SheetFlash.prototype.updateProgressbar = function()
{
	var currentTime = this.audioObj.getCurTime();
	var totalPlayTime = this.audioObj.getTotalTime();
	//$('.playTimeText').text(timeFormat(currentTime) + " / " + timeFormat(totalPlayTime));
	var per = currentTime/totalPlayTime * 100.0;
	$(this.className + ".progressBar" ).css('width', per + "%");
}

SheetFlash.prototype.setScale = function(targetName, scale)
{
	var obejct = $(targetName);
	this.scale = scale;
	var w = obejct.width()*scale;
	var h = obejct.height()*scale;
	obejct.width(w);
	obejct.height(h);
	var children = obejct.find('div');
	for(var i = 0; i < children.length; i++)
	{
		var child = $(children[i]);
		var w = child.width()*scale;
		var h = child.height()*scale;
		child.width(w);
		child.height(h);
		var t = parseFloat(child.css('top')) * scale;
		var l = parseFloat(child.css('left')) * scale;
		child.css('top', t + 'px');
		child.css('left', l + 'px');
	}
}

SheetFlash.prototype.eventSetting = function()
{
	var obj = this;
	var audioObj = this.audioObj;
	
	//audioObj에서 이벤트 추가
	var addEndEvent = function(){audioObj.addAudioEvent("ended", function(){
		console.log("common ended!");
		pauseBtn.css('display', 'none');
		playBtn.css('display', 'inline-block');
		
		obj.audioStop();
	})};
	addEndEvent();
	
	//시작 3초 후에 화면을 전환한다.
	var specialDefferedFunc = function(){
		var rTime = obj.curStartBeatPoint - 3;
		if(rTime < 0)
		{
			obj.toggleBackground(true);
		}
		else if(audioObj.getCurTime() == 0)
		{
			obj.toggleBackground(false);
			var func = setInterval(function(){
				if(audioObj.getCurTime() >= rTime)
				{
					obj.toggleBackground(true);
					clearInterval(func);
				}
			}, 1000);
		}
	};
	
	//button-event 추가
	var playBtn = $(this.className + '.playButton');
	var pauseBtn = $(this.className + '.pauseButton');
	var stopBtn = $(this.className + '.stopButton');
	var muteBtn = $(this.className + '.muteButton');
	var arBtn = $(this.className + '.arButton');
	var mrBtn = $(this.className + '.mrButton');
	playBtn.click(function(){
		playBtn.css('display', 'none');
		pauseBtn.css('display', 'inline-block');
		
		//obj.toggleBackground(true);
		specialDefferedFunc();
		
		obj.audioPlay();
	});
	pauseBtn.click(function(){
		pauseBtn.css('display', 'none');
		playBtn.css('display', 'inline-block');
		
		obj.audioPause();
	});
	stopBtn.click(function(){
		$('.partNumButton').removeClass('over');
		pauseBtn.css('display', 'none');
		playBtn.css('display', 'inline-block');
		
		obj.audioStop();
		
		if(obj.playMode == 1) obj.changeSource(obj.audioSrc);
		else if(obj.playMode == 2) obj.changeSource(obj.audioSrc_mr);
		
		audioObj.removeAudioEventAll('ended');
		addEndEvent();
	});
	muteBtn.click(function(){
		if(!$(this).hasClass('muteOffButton'))
			$(this).addClass('muteOffButton');
		else $(this).removeClass('muteOffButton');
		audioObj.toggleMute();
	});
	arBtn.click(function(){
		obj.playMode = 1;
		//audioObj.changeSource(obj.audioSrc);
	});
	mrBtn.click(function(){
		obj.playMode = 2;
		//audioObj.changeSource(obj.audioSrc_mr);
	});
	
	$('.type1Button').click(function(){
		efSound(playEffectSrc);
	});
	$('.type2Button').click(function(){
		//efSound(playEffectSrc);
		arBtn.removeClass('onClickButton');
		mrBtn.removeClass('onClickButton');
		if(!$(this).hasClass('onClickButton'))
			$(this).addClass('onClickButton');
		else $(this).removeClass('onClickButton');
		
		stopBtn.trigger("click");
		//obj.initPlayInfo(0, obj.startTime);
	});
	
	//처음 생성 시, ar버튼이 눌러져 있어야 한다.
	arBtn.trigger("click");
	
	//bar-event 추가
	var pbar = $(this.className + ".progressBar" );
	$(this.className + ".bar" ).click(function(e)
	{	
		if(audioObj.isAvailable())
		{
			efSound(playEffectSrc);
			var per = mouseX(e);
			audioObj.setCurTime(audioObj.getTotalTime() * per / 100.0);
			pbar.css('width', per + "%");
			
			obj.updateAllSubtitle();
		}
	});
	
	//partNumButton-event 추가
	var partBtns = $('.partNumButton');
	for(var i = 1; i <= partBtns.length; i++)
	{
		(function(e){$(partBtns[i - 1]).click(function(){
			stopBtn.trigger('click');
			
			$('.partNumButton').removeClass('over');
			$(this).addClass('over');
			
			obj.audioPartPlay(e);
			
			audioObj.addAudioEvent("ended", endEvent = function(){
				console.log("ended!");
				obj.initPlayInfo(obj.getPartIndex(e), 0);
				obj.toggleBackground(true);
				//audioObj.removeAudioEvent("ended", endEvent);
			});
		});})(i);
		
	}
	
	
	
	//사용자 이벤트
	//this.initEvent = onInit;
	//this.createEvent = onEndCreate;
	//this.updateEvent = onUpdate;
	//this.playEvent = onPlayStart;
	//this.stopEvent = onStop;
	//this.resetEvent = onResetSubtitle;
	//this.noReadyEvent = onNoReady;
	$(this).on('onInit', function(e){
		onInit(e);
	});
	$(this).on('createEvent', function(e){
		onEndCreate(e);
	});
	$(this).on('updateEvent', function(e, param_1){
		onUpdate(e, param_1);
	});
	$(this).on('playEvent', function(e){
		onPlayStart(e);
	});
	$(this).on('stopEvent', function(e){
		onStop(e);
	});
	$(this).on('resetEvent', function(e){
		onResetSubtitle(e);
	});
	$(this).on('noReadyEvent', function(e){
		onNoReady(e);
	});
	
}

SheetFlash.prototype.initSubtitle = function()
{
	console.log('initSubtitle');
	
	var obj = this;
	this.subtitle_orgs = null;
	
	//set subtitle_group
	this.subtitle_groups = $(this.className + '.subtitle_group');
	var groups = this.subtitle_groups;
	var groupCountPerSong = groups.length / this.songCounter;
	for(var i = 0; i < groups.length; i++)
	{
		//groups[i].setAttribute('id', this.id + 'group_' + i);
		var tImg = new Image();
		var fileNum = (i % groupCountPerSong);
		var imgSrc = subtitlePath + 'g' + fileNum + '.png';
		tImg.src = imgSrc;
		tImg.setAttribute('id', this.id + '#groupImage_' + i);
		(function(imgTempVar){
		tImg.onload = function() 
		{
			//var imgTempVar = this.getAttribute('id').split('_')[1];
			var fileNum = (imgTempVar % groupCountPerSong);
			
			var w = this.width;
			var h = this.height;
			var imageSize = w + 'px ' + h + 'px';
			
			var curGroup = groups[imgTempVar];
			$(curGroup).css('background', "url('" + subtitlePath + "g" + fileNum + ".png') center center no-repeat");
			$(curGroup).css('background-size', imageSize);
		}
		})(i);
	}
	
	//set subtitle
	return this.resetSubtitle(this.subtitleText);
}

SheetFlash.prototype.resetSubtitle = function(subtitleText)
{
	var orgs = this.subtitle_orgs;
	if(orgs == null) 
	{
		//자막 객체가 없다면 탐색을 시도한다.
		orgs = this.subtitle_orgs = $(this.className + '.subtitle');
		if(orgs == null) 
		{
			$(this).trigger("noReadyEvent");
			alert("subtitle객체가 없습니다.");
			return false;
		}
	}
	
	for(var i = 0; i < orgs.length; i++)
	{
		//subtitle_orgs[i].setAttribute('id', 'subtitle_' + i);
		var fileName = subtitleText[i];
		var imgSrc = subtitlePath + fileName + ".png";
		
		var tImg = new Image();
		tImg.src = imgSrc;
		//tImg.setAttribute('id', this.id + '#subtitleImage_' + i);
		(function(imgTempVar){
		tImg.onload = function(){
			//var imgTempVar = this.getAttribute('id').split('_')[1];
			var fileName = subtitleText[imgTempVar];
			
			var w = this.width;
			var h = this.height;
			
			var curSub = orgs[imgTempVar];
			
			//subtitle 설정
			curSub.style.width = w + 'px';
			//curSub.style.height = h + 'px';
			var imageSize = w + 'px ' + h + 'px';
			//console.log('loadname: ' + fileName);
			curSub.style.background = "url('" + subtitlePath + fileName + ".png') left center no-repeat";
			curSub.style.backgroundSize = imageSize;
			
			//subtitle_complete 설정
			var curSubChild = curSub.children[0];
			curSub.children[0].style.background = "url(" + subtitlePath +  fileName + "2.png) left center no-repeat";
			curSub.children[0].style.backgroundSize = imageSize;
		};
		})(i);
		
		//subtitle_complete 생성
		var curSub = $(orgs[i]);
		curSub.html("<div class='subtitle_complete'></div>");
	}
	
	$(this).trigger("resetEvent");
	
	return true;
}

SheetFlash.prototype.clearSubtitle = function()
{
	if(this.subtitle_orgs == null)
	{
		console.log('subtitle_orgs객체가 없습니다.');
		return;
	}
	$(this.subtitle_orgs).children('.subtitle_complete').css('width', '0%');
}

SheetFlash.prototype.initPlayInfo = function(startIdx, startTime)
{
	this.curIdx = startIdx;
	this.curStartBeatPoint = startTime;
	this.curEndBeatPoint = startTime + this.beats[startIdx] * this.perBeat;
	this.curSubtitle = $(this.subtitle_orgs[startIdx]).children();
	this.toggleBackground(false);
	this.updateBlock(this.curSubtitle);
	
	return true;
}

SheetFlash.prototype.toggleBackground = function(onoff)
{
	var box = $(this.className);
	var sheet = $(this.className + '.sheet');
	if(onoff)
	{
		box.addClass('noBackground');
		sheet.css('display', 'block');
	}
	else 
	{
		box.removeClass('noBackground');
		sheet.css('display', 'none');
	}
}

//모든 자막들을 해당 시간에 맞게 색칠한다.
SheetFlash.prototype.updateAllSubtitle = function()
{
	this.audioPause();
	
	var curTime = this.audioObj.getCurTime();
	if(curTime > this.curEndBeatPoint)
	{
		while(curTime > this.curEndBeatPoint)
		{
			this.curSubtitle.css('width', '100%');
			this.curIdx++;
			this.updateCurSubtitle(this.curIdx, true);
		}
	}
	else if(curTime < this.curStartBeatPoint)
	{
		while(curTime < this.curStartBeatPoint)
		{
			this.curSubtitle.css('width', '0%');
			this.curIdx--;
			this.updateCurSubtitle(this.curIdx, false);
		}
	}
	
	this.audioPlay();
}

//자막 갱신
SheetFlash.prototype.updateCurSubtitle = function(idx, isForward)
{		
	console.log('update: ' + idx);
	
	var curSubWrapper = $(this.subtitle_orgs[idx]);
	this.curSubtitle = curSubWrapper.children();
	
	var curBeat = this.beats[idx];
	var	curDuration = curBeat * this.perBeat;
	if(isForward)
	{
		this.curStartBeatPoint = this.curEndBeatPoint;
		this.curEndBeatPoint += curDuration;
	}
	else
	{
		this.curEndBeatPoint = this.curStartBeatPoint;
		this.curStartBeatPoint -= curDuration;
	}
	
	//this.updateEvent.curSubtitle = this.curSubtitle;
	$(this).trigger("updateEvent", [ this.curSubtitle ]);
	
}

SheetFlash.prototype.updateBlock = function(curSubWrapper)
{
	//console.log('updateBlock');
	$(this.className + '.sheet_page').css('display', 'none');
	curSubWrapper.parent().parent().parent().parent().css('display', 'block');
}

SheetFlash.prototype.audioPlay = function()
{
	this.audioObj.audioPlay();
	
	var obj = this;
	if(this.flashFunc == null) 
	{
		//this.toggleBackground(true);
		this.flashFunc = setInterval(function(){obj.progressSheetFlash(obj);}, 40);
	}
	
	$(this).trigger('playEvent');
}

SheetFlash.prototype.audioPartPlay = function(idx)
{
	var obj = this;
	this.audioStop();
	
	this.initPlayInfo((obj.getPartIndex = function(){
		var ret = 0;
		for(var i = 0; i < (idx - 1); i++)
		{
			ret += $(obj.subtitle_groups[i]).children('.sheetBlock').children('.subtitle').length;
		}
		return ret;
	})(), 0);
	
	var audioName;
	if(this.playMode == 1) audioName = mediaPath + idx + '.mp3';
	else if(this.playMode == 2) audioName = mediaPath + 'mr' + idx + '.mp3';
	
	var obj = this;
	var audio = this.audioObj;
	obj.changeSource(audioName);
	audio.addAudioEvent("loadedmetadata", autoLoadEvent = function(){
		$(obj.className + '.playButton').trigger("click");
		audio.removeAudioEvent("loadedmetadata", autoLoadEvent);
	});
	
	
	
}

SheetFlash.prototype.audioPause = function()
{
	this.audioObj.audioPause();
	
	if(this.flashFunc !== null) 
	{
		clearInterval(this.flashFunc);
		this.flashFunc = null;
	}
	
	this.updateProgressbar();
}

SheetFlash.prototype.audioStop = function()
{
	this.audioPause();
	
	this.clearSubtitle();
	
	//if(this.playMode == 1) this.audioObj.changeSource(this.audioSrc);
	//if(this.playMode == 2) this.audioObj.changeSource(this.audioSrc_mr);
	this.initPlayInfo(0, this.startTime);
	$(this.className + ".progressBar" ).css('width', "0%");
	
	$(this).trigger('stopEvent');
}

SheetFlash.prototype.progressSheetFlash = function(obj)
{
	//subtitle progress check
	var curTime = obj.audioObj.getCurTime();
	var per = (curTime - obj.curStartBeatPoint) / (obj.curEndBeatPoint - obj.curStartBeatPoint) * 100.0;
	if(per <= 110 && per >= 0 && obj.curSubtitle) 
	{
		obj.curSubtitle.css('width', per + '%');
	}
	
	//subtitle update
	if(curTime >= obj.curEndBeatPoint)
	{
		if(obj.curSubtitle) 
		{
			obj.curSubtitle.css('width', '100%');
		}
		obj.curIdx++;
		obj.updateCurSubtitle(obj.curIdx, true);
	}
	
	obj.updateProgressbar();
}




//prototype event
//SheetFlash.prototype.initEvent = jQuery.Event("initEvent", {  });
//SheetFlash.prototype.createEvent = jQuery.Event("createEvent", {  });
//SheetFlash.prototype.updateEvent = jQuery.Event("updateEvent", {  });
//SheetFlash.prototype.playEvent = jQuery.Event("playEvent", {  });
//SheetFlash.prototype.stopEvent = jQuery.Event("stopEvent", {  });

//이벤트가 발생했을 시 호출되는 함수: 재정의해서 사용
//초기화가 끝난 후에 작업 재정의
function onInit() { /*console.log('onInit');*/ }
//생성이 끝난 후에 작업 재정의
function onEndCreate() { /*console.log('onCreate');*/ }
//자막이 갱신될 때마다 작업 재정의
function onUpdate(e, param_1) 
{ 
	e.target.updateBlock(param_1);
	//this.updateBlock(this.updateEvent.curSubtitle);
}
function onPlayStart() {}
function onStop() {}
function onResetSubtitle() {}
function onNoReady() {}



/* class: SheetFlashAudio */
function SheetFlashAudio(className, src)
{
	//set property
	this.className = className;
	this.name = className + '.audioPanel';
	this.panel = $(this.name);
	this.srcObj = this.panel.children('source')[0];
	this.eventSetting();
	
	//local variable
	var audioPanel = this.panel;
	
	//function
	this.changeSource(src);
	
	//this.panel.on('loadedmetadata', function() 
	//{		
	//	//this.onended = function()
	//	//{	
	//	//	$(this).trigger('endEvent');
	//	//}
	//	
	//	//$(this).trigger('loadEvent');
	//	
	//});
	
	var obj = this;
	return{
		//getPanel : function(){
		//	return audioPanel;
		//},
		getCurTime : function(){
			return audioPanel.prop("currentTime");
		},
		setCurTime : function(curTime){
			audioPanel.prop("currentTime", curTime);
		},
		getTotalTime : function(){
			return audioPanel.prop("duration");
		},
		isAvailable : function(){
			return !isNaN(audioPanel.prop("duration"));
		},
		changeSource : function(src){
			obj.changeSource(src);
		},
		audioPlay : function(){
			audioPanel.trigger('play');
		},
		audioPause : function(){
			audioPanel.trigger('pause');
		},
		toggleMute : function(){
			audioPanel.prop("muted",!audioPanel.prop("muted"));
		},
		addAudioEvent : function(e, func){
			audioPanel.on(e, func);
		},
		removeAudioEvent : function(e, func){
			audioPanel.off(e, func);
		},
		removeAudioEventAll : function(e){
			audioPanel.off(e);
		},
		setAudioSpeed : function(speed){
			audioPanel.prop("playbackRate", speed);
		},
		setAudioVolume : function(vol){
			audioPanel.prop("volume",vol);
		}
		
	}
	
}

SheetFlashAudio.prototype.changeSource = function(src)
{
	console.log('change source.');
	this.srcObj.setAttribute('src', src);
	this.panel.load();
}

SheetFlashAudio.prototype.eventSetting = function()
{
	//this.loadEvent = onLoad;
	//this.endEvent = onEnd;
	
}

//prototype event
//SheetFlashAudio.prototype.loadEvent = jQuery.Event("loadEvent", {  });
//SheetFlashAudio.prototype.endEvent = jQuery.Event("endEvent", {  });

////이벤트가 발생했을 시 호출되는 함수
////로드가 끝난 후에 작업 재정의
//function onLoad() { console.log('onLoad'); }
////플레이가 끝난 후에 작업 재정의
//function onEnd() { console.log('onEnd'); }



//non-member global function
// 위치값을 찾아서 퍼센트(%) 반환
function mouseX (e) {
	e = e || window.event;
	
	var p1 = $('.bar').offset().left;
	var p2 = e.pageX;
	var p3 = $('.bar_rightPoint').offset().left;
	
	var percentage = 100 * ((p2 - p1) / (p3 - p1));
	
	if(percentage > 100) {
		percentage = 100;		
	} else if(percentage < 0) {
		percentage = 0;		
	}

	return percentage;
}




