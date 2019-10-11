// ==UserScript==
// @name         HatBar
// @namespace    https://github.com/rikonek/job
// @version      0.3
// @description  Work time counter
// @author       Rikon
// @match        https://hat.poland.[YOUR_DOMAIN_HERE].com/*
// @grant        GM_addStyle
// @require      http://code.jquery.com/jquery-3.3.1.min.js
// ==/UserScript==

GM_addStyle(`
	#hatbar { position: fixed; z-index: 999; top: 0px; border-bottom: 1px solid #cccccc; background-color: yellow; width: 100%; padding: 7px; text-align: center; }
	#hatbar_synchro { position: absolute; top: 5px; right: 20px; }
	#hatbar_time_fix { background: #ffffff; border: 1px solid #aaaaaa; width: 150px; font-weight: normal; }
`);

function init()
{
	addBar();

	$('#hatbar_time_fix').change(function() {
		setTimeFix($(this).val());
		location.reload();
	});

	$('#hatbar_time_fix').val(get('manual_time_fix'));

	getWorkTime();
}

function set(key,value)
{
	localStorage.setItem('hatbar_'+key,value);
}

function get(key)
{
	return localStorage.getItem('hatbar_'+key);
}

function addBar()
{
	$('body').prepend('<div id="hatbar">Czas pracy: <span id="hatbar_today">00:00:00</span>, Koniec: <span id="hatbar_end">00:00</span> (<span id="hatbar_remaining">00:00:00</span>)<br />Do wypracowania: <span id="hatbar_estimated">00:00:00</span>, Wypracowane: <span id="hatbar_sum">00:00:00</span><div id="hatbar_synchro"><input type="text" id="hatbar_time_fix" placeholder="Korekta czasu [minuty]" /></div></div>');
}

function getEvents(date)
{
	$.get("/activities/get-access-events/"+date,function(d) {
		d=eval(d);
		var tab={};
		$.each(d,function(index,value) {
			if(!tab[value.u])
			{
				tab[value.u]=[];
			}
			tab[value.u].push(value.det.tm);
		});
		readTimeFromEvents(tab);
		refreshTime();
	});
}

function readTimeFromEvents(tab)
{
	$('#content').append("<br /><br />");
	$.each(tab,function(data,arr) {
		tab[data].sort();
		var start=new Date(arr[0]);
		var end=new Date(arr[arr.length-1]);
		var d=start.toISOString().replace('-','').replace('-','').substr(0,8);
		var now=new Date();
		t=now.toISOString().replace('-','').replace('-','').substr(0,8);
		if(d==t)
		{
			today_start=start;
			end=now;
		}
	});
}

function getWorkTime()
{
	var now=new Date();
	now=now.toISOString().substr(0,10);
	var time_div=$('div.s');
	$.each(time_div,function(index,value) {
		if($(this).attr('id')==now)
		{
			getEvents(now.substr(0,7));
		}
		else
		{
			month_estimated+=parseInt($(this).attr('norm'))*3600*1000;
			month_sum+=parseInt($(this).attr('sum'))*1000;
		}
	});
	month_sum+=get('manual_time_fix')*60*1000;
	refreshConstTime();
}

function tFormat(t,sec=1)
{
	if(t<0)
	{
		t=t*(-1);
	}
	t=t/1000;
	h=parseInt(t/3600,0);
	m=parseInt((t-(h*3600))/60);
	s=parseInt(t-(h*3600)-(m*60));
	if(h<10)
	{
		ti=("0"+h).slice(-2);
	}
	else
	{
		ti=h;
	}
	ti=ti+':'+("0"+m).slice(-2);
	if(sec==1)
	{
		ti=ti+':'+("0"+s).slice(-2);
	}
	return ti;
}

function getTodayTime()
{
	now=new Date();
	diff=now-today_start;
	return diff;
}

function getEndTime()
{
	diff=month_sum-month_estimated;
	start=(today_start.getHours()*3600+today_start.getMinutes()*60+today_start.getSeconds())*1000;
	end=(8*3600*1000)+start-diff;
	return end;
}

function getRemainingTime()
{
	currdate=new Date();
	now=(currdate.getHours()*3600+currdate.getMinutes()*60+currdate.getSeconds())*1000;
	remaining=getEndTime()-now;
	if(remaining<0)
	{
		remaining=remaining*(-1);
		remaining_sign='+';
	}
	else
	{
		remaining_sign='-';
	}
	return remaining_sign+tFormat(remaining);
}

function refreshConstTime()
{
	$('#hatbar_estimated').html(tFormat(month_estimated));
	$('#hatbar_sum').html(tFormat(month_sum));
}

function refreshTime()
{
	if(!today_start) return false;
	$('#hatbar_today').html(tFormat(getTodayTime()));
	$('#hatbar_remaining').html(getRemainingTime());
	$('#hatbar_end').html(tFormat(getEndTime(),0));
}

function parseTime(str)
{
	var s=str.split(':');
	return (s[0]*3600+s[1]*60+s[2]*1)*1000;
}

function setTimeFix(value)
{
	val=parseInt(value);
	if(val==0 || !$.isNumeric(val)) val='';
	set('manual_time_fix',val);
}

var today_start;
var month_estimated=0;
var month_sum=0;

(function() {
	'use strict';

	init();
	setInterval(function() { refreshTime(); },1000);
})();