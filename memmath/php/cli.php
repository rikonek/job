#!/usr/bin/env php
<?php
error_reporting(E_ALL ^ E_NOTICE);
setlocale(LC_ALL, 'pl_PL.UTF-8', 'polish_poland.65001', 'polish_poland');
date_default_timezone_set('Europe/Warsaw');

require_once('memmath.class.php');

if ($argc < 3) {
    echo('Usage:' . PHP_EOL);
    echo('  ' . $argv[0] . ' arg1 arg2 [...]' . PHP_EOL);
    exit();
}

$m=new Memmath();
foreach ($argv as $index=>$arg) {
    if ($index==0) {
        continue;
    }
    $m->addNumber($arg);
}
while ($m->sum());
