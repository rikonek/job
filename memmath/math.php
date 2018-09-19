#!/usr/bin/env php
<?php
error_reporting(E_ALL ^ E_NOTICE);
setlocale(LC_ALL,'pl_PL.UTF-8','polish_poland.65001','polish_poland');
date_default_timezone_set('Europe/Warsaw');

$add=array(
  array('val'=>$argv[1], 'len'=>strlen($argv[1])),
  array('val'=>$argv[2], 'len'=>strlen($argv[2])),
);
$add_str=array();
$max_len=0;
foreach($add AS $tmp)
{
  if($tmp['len']>$max_len) $max_len=$tmp['len'];
}
$max_len+=3;
foreach($add AS $tmp)
{
  $diff=$max_len-$tmp['len'];
  $new_val='';
  for($i=0;$i<$diff;$i++)
  {
    $new_val.=' ';
  }
  $new_val.=$tmp['val'];
  $add_str[]=$new_val;
}
$op='';
$res='';
for($i=0;$i<$max_len;$i++)
{
  $op.='0';
  $res.='0';
}
for($i=($max_len-1);$i>=0;$i--)
{
  $tmp_sum=0;
  foreach($add_str AS $tmp)
  {
    $tmp_sum+=(int)$tmp[$i];
  }
  $tmp_sum+=(int)$op[$i];
  $tmp_sum_s=(string)$tmp_sum;
  if(strlen($tmp_sum_s)==2)
  {
    $op[$i-1]=$tmp_sum_s[0];
    $res[$i]=$tmp_sum_s[1];
  }
  else
  {
    $op[$i-1]=0;
    $res[$i]=$tmp_sum_s[0];
  }
}
$op=str_replace('0',' ',$op);
echo($op."\r\n");
$max_add_str=count($add_str);
for($i=0;$i<$max_add_str;$i++)
{
  if($i==($max_add_str-1)) $add_str[$i][0]='+';
  echo($add_str[$i]."\r\n");
}
for($i=0;$i<$max_len;$i++)
{
  echo('-');
}
echo("\r\n");
for($i=0;$i<strlen($res);$i++)
{
  if($res[$i]=='0')
  {
    $res[$i]=' ';
  }
  else break;
}
echo($res."\r\n");