/*flashSetting*/
$(document).ready(function(){
	
	//subtitleSetting();
	
});

//subtitle이 없을 때 발생한다.
function onNoReady(e)
{
	//subtitleSetting();
}

/*global variable*/
var selected = null;



//function Map(classes)
//{
//	var map = this;
//	$(classes).each(function(){
//		map[this] = { obj: null, update: null };
//		(map[this].obj = $( "." + this )).attr('name', this);
//		//console.log(map[this]);
//	});
//}

/*class ClassDictionary*/
function ClassDictionary()
{
	this.classes = ["sheetFlashPaper", "sheet", "sheet_page", "subtitle_group", "sheetBlock", "subtitle", "numCircleGreen", "videoPlayBar", "subtitle_complete"];
	//inner class Map
	this.Map = function(classes)
	{
		var map = this;
		$(classes).each(function(){
			map[this] = { obj: null, update: null };
			(map[this].obj = $( "." + this )).attr('name', this);
			//console.log(map[this]);
		});
		
		//set update function
		map["sheetFlashPaper"].update = function(){
			
		}
	};
	this.classMap = new this.Map(this.classes);
	
	console.log(this.classMap);
	
}



//클래스 접근 객체
var dic = new ClassDictionary();

function subtitleSetting()
{
	alert("html문서를 수정합니다.");
	console.log("subtitleSetting");
	
	//접근을 위한 이름 부여
	//var classes = ["sheetFlashPaper", "sheet", "sheet_page", "subtitle_group", "sheetBlock", "subtitle", "numCircleGreen"]
	
	//var id = 0;
	//var sheets = $('.sheetFlashPaper');
	//sheets.each(function(){
	//	$(this).attr('id', 'flashPaper_' + id);
	//});
	//
	//var sheets = $('.imageFlashPaper');
	//sheets.each(function(){
	//	$(this).attr('id', 'flashPaper_' + id);
	//});
	
	var subtitles = $('.subtitle');
	subtitles.draggable({
		axis: "x, y",
		stop : function(){
			var curLocation = $(this).offset();
			$(this).offset({top: parseInt((curLocation.top)/20)*20});
		},
		disabled: false
	});
	//setDraggablefixX(subtitles);
	setDraggableFree(selected);
	
	var typeCheck = function(){
		return typeof $(selected).attr('name') !== 'undefined';
	}
	//click target
	$(document).click(function(e){
		
		if(selected !== null && typeCheck()) 
		{
			$(selected).removeClass('lineBox');
			//setRelease(selected);
		}
		
		selected = e.target;
		
		if(!typeCheck()) return;
		$(selected).addClass('lineBox');
		
	});
	
}

function setDraggablefixX(target)
{
	$(target).draggable( "option", "axis", "x" );
}

function setDraggableFree(target)
{
	$(target).draggable( "option", "disabled", false );
	//target.draggable( "option", "axis", false );
	$(target).draggable( "option", "axis", "x, y" );
}

function setTargetMutable(target)
{
	$(target).draggable( "option", "disabled", false );
}

//function setTargetConstant()
//{
//	var t = $(selected);
//	$( ".selector" ).draggable({
//		disabled: true
//	});
//	t.draggable( "option", "disabled", true );
//	
//}

function setRelease(target)
{
	//$(target).draggable( "option", "disabled", true );
}

function setPosition(obj, x, y){
	$(obj).offset({top: x, left: y});
}



