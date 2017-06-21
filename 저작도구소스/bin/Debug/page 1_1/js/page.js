function addJavascript(jsname) {
	var th = document.getElementsByTagName('head')[0];
	var s = document.createElement('script');
	s.setAttribute('type','text/javascript');
	s.setAttribute('src',jsname);
	th.appendChild(s);
}
//addJavascript('./js/jquery-1.12.2.min.js');

function load_function(){
}
$(document).ready(function() {
	
	initWindow();
	
	setQbox();
	
	//playNarration();
	
	//위치정보파악
	if($('#mouseLog').length > 0)
	{
		var txt = "";
		var margin = 0;
		$(".sheetBlock").mousedown(function(){
			margin = $(this).offset().left;
		});
		$(".innerBox").mousedown(function(e){
			txt = 'mouse: ' + (e.pageX - margin) + '/' + e.pageY; 
			$('#mouseLog').html(txt);
		});
	}
	
});
function effectImage(fadeInTime, delayTime, fadeOutTime)
{
	$("#overlay").fadeIn(fadeInTime).delay(delayTime).fadeOut(fadeOutTime);
}
function effectSound() {
	$("#effect_audio").trigger("play");
}
function setEffectImage(bgImage) {
	$("#effect_holder").css("background-image", "url('" + bgImage + "')");
}
function setEffectSound(bgSound) {
	$("#effect_audio").attr("src", bgSound);
}
function image_click(id){
}

/***variable********************************************************************/
var imagePath = './images/common/';
var mediaPath = './media/';
var containerType;
var narrationAudioSrc = mediaPath + 'n.mp3';

var clickAudioSrc = mediaPath + 'playerButton_1.mp3';
var correctAudioSrc = mediaPath + 'correct.mp3';
var inCorrectAudioSrc = mediaPath + 'incorrect.mp3';

// ******************************************************************
// 효과음
function playNarration()
{
	setTimeout(function(){
		
		if(!efSound(narrationAudioSrc))
		{
			console.log('나레이션 파일이 없습니다.');
		}
		
	}, 1000);
	
}

function efSound (src) {
	var efAudio = new Audio;
	var efPlay = function () {
		efAudio.removeEventListener('loadeddata', efPlay);
		efAudio.play();
	};
	efAudio.src = src;
	efAudio.addEventListener('loadeddata', efPlay);
	efAudio.load();
	
	return true;
}

var globalAudio = new Audio;

globalAudio.addEventListener('loadeddata', onGlobalAudioLoad);
//onGlobalAudioLoad
function onGlobalAudioLoad()
{
	globalAudio.play();
}

function globalAudioPlay(src) {
	globalAudio.src = src;
	globalAudio.load();
}

function globalAudioVolumeCtrl(vol)
{
	if(globalAudio == null) 
	{
		console.log('오디오가 없습니다.');
		return;
	}
	if(vol < 0 || vol > 1.0)
	{
		console.log('볼륨이 잘못되었습니다.');
		return;
	}
	
	$(globalAudio).prop("volume", vol);
}

$(globalAudio).on('onsuspend', function(){
	this[0].pause();
});

//normal
function initWindow()
{
	//타입 체크
	if($('.openingContainer'))
	{
		containerType = 1;
	}
	else if($('.activeContainer'))
	{
		containerType = 2;
	}
	
	//팝업창 체크
	if($('.popupContainer'))
	{
		initPopupWindow();
	}
	
	var isDoubleLine = $('.doubleLineTitle');
	for(var id = 0; id < isDoubleLine.length; id++)
	{
		isDoubleLine[id].setAttribute('id', 'container_' + id);
	}
	
	for(var id = 0; id < isDoubleLine.length; id++)
	{
		var object = $('#container_'  + id);
		
		var titleObject = object.children('.contentsTitle');
		var contentsObject = object.children('.contentsBox');
		
		//현재 객체 타입 확인
		var type;
		if(object.hasClass('openingContainer')) type = 1;
		else if(object.hasClass('activeContainer')) type = 3;
		else if(object.hasClass('popupContainer')) type = 3;
		
		//css 갱신
		titleObject.css('height', '203px');
		titleObject.css('background-image', "url('" + imagePath + 'phase' + type + 'Cloud2.png' +"')");
		
		contentsObject.css('top', '198px');
		contentsObject.css('height', '563px');
		contentsObject.css('background-size', '992px 563px');
	}
	
}

//popup
//popup window check
function initPopupWindow()
{
	var popupButton = $(".popupButton");
	if(popupButton)
	{
		var popupWindow = $('.popupContainer');
		if(popupWindow == null)
		{
			console.log('팝업 컨테이너가 있어야 합니다.');
			return;
		}
		
		popupButton.click(function(e) 
		{
			popupWindow.css('display', 'inline');
		});
		
		$(".closeButton").click(function(e) 
		{
			popupWindow.css('display', 'none');
		});
	}
}

function setQbox()
{
	var boxes = $('.qBox');
	if(boxes.length > 0)
	{
		boxes.children('.qBoxBg').append('<div class="qIcon"></div>');
		for(var i = 0; i < boxes.length; i++)
		{
			boxes[i].setAttribute('id', 'box_' + i);
		}
		
		boxes.click(function(e)
		{
			var box = $('#' + this.getAttribute('id'));
			
			box.css('background', 'white');
			box.children('.qBoxBg').css('background', 'transparent');
			fade(box.children('.qBoxBg').children('.qIcon'), 0);
			fade(box.children('.qBoxBg').children('.qText'), 1);
			
			box.unbind( 'click' );   // click 이벤트 제거
			box.css('cursor', 'auto');
		});
	}
}

//onoff -> 1: 켠다 0: 끈다.
function fade(target, onoff)
{
	var fadeFunc = setInterval(function()
	{
		var op = parseFloat(target.css('opacity'));
		
		if(onoff && op <= 1.0)
		{
			op += 0.1;
			target.css('opacity', op);
		}
		else if(!onoff && op >= 0.0)
		{
			op -= 0.1;
			target.css('opacity', op);
		}
	}, 60);
	
	setTimeout(function()
	{
		clearInterval(fadeFunc);
	}, 3000);
}

//common button event
$('.customPlayButton').click(function(){
	efSound(clickAudioSrc);
	
});



/***init********************************************************************/

/*
	create date : 2016-05-19
	creator : saltgamer
*/
'use strict';

/*function runTextBook (callBack) {

	if(window.document){
     
        if ( window.document.readyState === "complete" ) {
            setTimeout( run );
        } else {
            // window.document.addEventListener( "DOMContentLoaded", completed, false );
            window.addEventListener("load", completed, false );
        }
    }
    function completed() {
        // window.document.removeEventListener( "DOMContentLoaded", completed, false );
        window.removeEventListener( "load", completed, false );
        callBack();
    }
}

var FORTEACHERCD = FORTEACHERCD || {};

FORTEACHERCD.responsive = (function () {

	var responsive = {
		baseContainerSize : {		
			width : 1024,
			height : 768
		}, 
		currentContainerSize : {
			containerWidth : window.innerWidth || document.documentElement.clientWidth || document.body.clientWidth,
			containerHeight : window.innerHeight || document.documentElement.clientHeight || document.body.clientHeight	
		},
		setScaleElement : function (targetElement, adjust) {			
		   	var bgContainer = document.querySelector('#bgContainer'),
		   		zoomVertical = this.currentContainerSize.containerHeight / targetElement.clientHeight,
				zoomHorizontal = this.currentContainerSize.containerWidth / targetElement.clientWidth;													

			var	zoomVerticalBg = (this.currentContainerSize.containerHeight / bgContainer.clientHeight) * 1.0;
			var	zoomHorizontalBg = (this.currentContainerSize.containerWidth / bgContainer.clientWidth) * 1.0;					
			
						
			if (targetElement.clientWidth * zoomVertical > this.currentContainerSize.containerWidth) {
				this.setTransformCSS(targetElement, zoomHorizontal);
				this.setTransformCSS(bgContainer, zoomHorizontalBg);

			} else {
				this.setTransformCSS(targetElement, zoomVertical);
				targetElement.style.left = ((this.currentContainerSize.containerWidth - (targetElement.clientWidth * zoomVertical)) / 2)  + 'px';
				
				this.setTransformCSS(bgContainer, zoomVerticalBg);
				bgContainer.style.left = ((this.currentContainerSize.containerWidth - (bgContainer.clientWidth * zoomVerticalBg)) / 2)  + 'px';
			}
			
		},
		setTransformCSS : function (targetElement, zoomRate) {
			targetElement.setAttribute('style', '-ms-transform: scale(' + zoomRate + ',' + zoomRate + ');' 
				+ '-webkit-transform: scale(' + zoomRate + ',' + zoomRate + ');' + 'transform: scale(' + zoomRate + ',' + zoomRate + ');' 
				+ 'transform-origin: 0% 0%; -webkit-transform-origin: 0% 0%; -ms-transform-origin: 0% 0%;');		
		}
	};
	return responsive;	
})();

// runTextBook
runTextBook(function () {

	FORTEACHERCD.responsive.setScaleElement(document.querySelector('#frameContainer'));

	window.addEventListener('resize', function () {		
		FORTEACHERCD.responsive.currentContainerSize.containerWidth = window.innerWidth || document.documentElement.clientWidth || document.body.clientWidth;
		FORTEACHERCD.responsive.currentContainerSize.containerHeight = window.innerHeight || document.documentElement.clientHeight || document.body.clientHeight;
		FORTEACHERCD.responsive.setScaleElement(document.querySelector('#frameContainer'));
	}, false);

	//setTimeout(function () {
	//	document.querySelector('#loadingContainer').style.display = 'none';
	//	setTimeout(function () {
	//		var animateOption1 = {
	//			left: -10,
	//			right : -10,
	//			delta : makeEaseInOut(quad),
	//			delay : 1,
	//			duration : 200
	//		};
	//	}, 150);
	//}, 250);
    //
	//if (QS('#contents')) setTimeout(function(){ QS('#contents').style.opacity = 1 }, 300);
	//initSound ();
});

var eventCheck = 'ontouchstart' in window || window.DocumentTouch && document instanceof DocumentTouch;
// log(eventCheck);

var gameManager = {
		eventSelector : {
		downEvent : eventCheck ? 'touchstart' : 'mousedown',
		moveEvent : eventCheck ? 'touchmove' : 'mousemove',
		upEvent : eventCheck ? 'touchend' : 'mouseup',
		outEvent : eventCheck ? 'touchleave' : 'mouseout'
	}
}

function initScale() {

	var wrap = document.getElementById('frameContainer');

	gameManager.clientWidth = document.body.clientWidth;
	gameManager.clientHeight = document.body.clientHeight;

	gameManager.wrapWidth = wrap.clientWidth;
	gameManager.wrapHeight = wrap.clientHeight;

	gameManager.zoomVertical = (gameManager.clientHeight / gameManager.wrapHeight) * 1;
	gameManager.zoomHorizontal = (gameManager.clientWidth / gameManager.wrapWidth) * 1;

	if (gameManager.wrapWidth * gameManager.zoomVertical < gameManager.clientWidth) {

		setScaleMainArea(wrap, gameManager.zoomVertical);
		gameManager.zoomRate = gameManager.zoomVertical;

	} else {

		setScaleMainArea(wrap, gameManager.zoomHorizontal);
		gameManager.zoomRate = gameManager.zoomHorizontal;

	}

	console.log("gameManager.zoomRate : " + gameManager.zoomRate);
}

function getRealOffsetTop(o) { return o ? o.offsetTop + getRealOffsetTop(o.offsetParent) : 0; }
function getRealOffsetLeft(o) { return o ? o.offsetLeft + getRealOffsetLeft(o.offsetParent) : 0; }

function setScaleMainArea(targetElement, zoomRate) {
	targetElement.setAttribute('style', '-ms-transform: scale(' + zoomRate + ',' + zoomRate + ');' + '-webkit-transform: scale(' + zoomRate + ',' + zoomRate + ');' + 'transform: scale(' + zoomRate + ',' + zoomRate + ');' + 'transform-origin: 0% 0%; -webkit-transform-origin: 0% 0%; -ms-transform-origin: 0% 0%;');
}*/

// $(function() {

// 	//폴더오픈
// 	$("#btn").click(function(e) {
// 		try {
// 			//msg
// 			window.external.CallMsg("인증이 완료되었습니다.");
// 			//c# 함수 호출
// 			window.external.CallFolderOpen("data\\Lesson1\\step01\\1단원_교수_학습_모형_과정안(교과서_12쪽).hwp");
// 		} catch (e) {
// 			console.log(e);
// 		}
// 	});
