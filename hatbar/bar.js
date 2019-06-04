// ==UserScript==
// @name         HatBar
// @namespace    https://github.com/rikonek/job
// @version      0.2
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

	$('#hatbar_synchro_button').click(function() {
		hatSummarySynchronization();
		location.reload();
	});
	$('#hatbar_time_fix').change(function() {
		setTimeFix($(this).val());
		location.reload();
	});

	$('#hatbar_time_fix').val(get('manual_time_fix'));

	var now=new Date();
	getEvents(now.toISOString().substr(0,7));
	month_sum=month_sum+(get('manual_time_fix')*60*1000);
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
	$('body').prepend('<div id="hatbar">Czas pracy: <span id="hatbar_today">00:00:00</span>, Koniec: <span id="hatbar_end">00:00</span> (<span id="hatbar_remaining">00:00:00</span>)<br />Do wypracowania: <span id="hatbar_estimated">00:00:00</span>, Wypracowane: <span id="hatbar_sum">00:00:00</span><div id="hatbar_synchro"><input type="text" id="hatbar_time_fix" placeholder="Korekta czasu [minuty]" /> <button id="hatbar_synchro_button">Synchronizuj</button></div></div>');
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
		refreshConstTime();
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
		diff=0;
		if(d==t)
		{
			today_start=start;
			end=now;
		}
		else
		{
			diff=end-start;
		}
		month_estimated=month_estimated+(8*3600*1000);
		month_sum=month_sum+diff;
		month_events=month_events+diff;
		$('#content').append(d+": "+tFormat(diff)+"<br />");
	});
	month_estimated=month_estimated-(8*3600*1000);
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
	$('#hatbar_end').html(tFormat(getEndTime(),0));
	$('#hatbar_estimated').html(tFormat(month_estimated));
	$('#hatbar_sum').html(tFormat(month_sum));
}

function refreshTime()
{
	$('#hatbar_today').html(tFormat(getTodayTime()));
	$('#hatbar_remaining').html(getRemainingTime());
}

function parseTime(str)
{
	var s=str.split(':');
	return (s[0]*3600+s[1]*60+s[2]*1)*1000;
}

function hatSummarySynchronization()
{
	time_div=$('div.m span');
	time=[];
	$.each(time_div,function(index,value) {
		time.push(value.innerHTML.replace(/\s+\(.*\)/,''));
	});
	total_counted=parseTime(time[0])+parseTime(time[2]);
	diff=total_counted-month_estimated;
	diff_events=month_events-month_estimated;
	setTimeFix(parseInt((diff-diff_events)/60/1000));
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
var month_events=0;

(function() {
	'use strict';

	init();
	setInterval(function() { refreshTime(); },1000);
})();