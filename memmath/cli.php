#!/usr/bin/env php
<?php
error_reporting(E_ALL ^ E_NOTICE);
setlocale(LC_ALL,'pl_PL.UTF-8','polish_poland.65001','polish_poland');
date_default_timezone_set('Europe/Warsaw');

require_once('memmath.class.php');

$count_arg=count($argv);
if($count_arg<3)
{
  echo('Usage:'."\r\n");
  echo($argv[0].' arg1 arg2 [...]');
  exit();
}

$m=new memmath();
foreach($argv AS $index=>$arg)
{
  if($index==0) continue;
  $m->addNumber($arg);
}
while($m->sum());

//$m=new math();
//$m->addNumber(5555);
//$m->addNumber(666);
//$m->addNumber(777);
//$m->addNumber(8888);
//$m->addNumber(99999);
//$m->addNumber(2);
//
//while($m->sum());