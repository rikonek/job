$(document).ready(function() {

  $('body').prepend('<div style="position: fixed; z-index: 999; top: 0px; border-bottom: 1px solid #cccccc; background-color: yellow; width: 100%; padding: 7px; text-align: center;">Czas pracy: <span id="mn_today"></span>, Koniec: <span id="mn_end"></span> (<span id="mn_remaining"></span>)<br />Do wypracowania: <span id="mn_estimated"></span>, Wypracowane: <span id="mn_sum"></span></div>');

  var today_start;
  var month_estimated=0;
  var month_sum=0;
  
  setInterval(function() { refreshTime(); },500);

  function tFormat(t,sec=1)
  {
    t=t/1000;
    h=parseInt(t/3600,0);
    m=parseInt((t-(h*3600))/60);
    s=parseInt(t-(h*3600)-(m*60));
    ti=("0"+h).slice(-2)+':'+("0"+m).slice(-2);
    if(sec==1)
    {
      ti=ti+':'+("0"+s).slice(-2);
    }
    return ti;
  }

  function refreshTime()
  {
    now=new Date();
    diff=now-today_start;
    $('#mn_today').html(tFormat(diff));
    sum=month_sum+diff;
    $('#mn_remaining').html(tFormat(month_estimated-sum));
    end_h=now.getHours()*3600*1000;
    end_m=now.getMinutes()*60*1000;
    end=end_h+end_m;
    $('#mn_end').html(tFormat(end+month_estimated-sum,0));
  }
  
  var tab={};
  gd=new Date();
  gt=gd.toISOString().substr(0,7);
  $.get("/activities/get-access-events/"+gt,function(data) {
    data=eval(data);
    $('#content').append("<br /><br />");
    $.each(data,function(index,value) {
      if(!tab[value.u])
      {
        tab[value.u]=[];
      }
      tab[value.u].push(value.det.tm);
    });
    $.each(tab,function(data,arr) {
      start=new Date(arr[0]);
      end=new Date(arr[arr.length-1]);
      d=start.toISOString().replace('-','').replace('-','').substr(0,8);
      dn=new Date();
      t=dn.toISOString().replace('-','').replace('-','').substr(0,8);
      diff=0;
      if(d==t)
      {
        today_start=start;
        end=dn;
      }
      else
      {
        diff=end-start;
      }
      month_estimated=month_estimated+(8*3600*1000);
      month_sum=month_sum+diff;
      $('#content').append(d+": "+tFormat(diff)+"<br />");
    });
    $('#mn_estimated').html(tFormat(month_estimated-(8*3600*1000)));
    $('#mn_sum').html(tFormat(month_sum));
  });


});
