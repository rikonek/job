<?php

class memmath
{
  private $numbers=array();
  private $max_len_number=0;
  private $sign_space=2; // ex. '+ '
  private $helper='';
  private $result='';
  private $result_addition=2; // min 1 - space before number (extra sign for result)

  public function addNumber($num): void
  {
    $num=(string)((int)$num);
    $this->numbers[]=$num;
  }

  public function sum()
  {
    if(!$this->checkMinNumbers()) return false;
    $this->operSum($this->numbers[0],$this->numbers[1]);

    $this->helper=str_replace('0',' ',$this->helper);
    echo($this->makeSpaceString($this->sign_space).$this->helper."\r\n");
    echo($this->makeSpaceString($this->sign_space).$this->numbers[0]."\r\n");
    $str=$this->makeSpaceString($this->sign_space).$this->numbers[1]."\r\n";
    $str[0]='+';
    echo($str);

    for($i=0;$i<($this->max_len_number+$this->sign_space);$i++)
    {
      echo('-');
    }
    echo("\r\n");
    for($i=0;$i<strlen($this->result);$i++)
    {
      if($this->result[$i]=='0')
      {
        $this->result[$i]=' ';
      }
      else break;
    }
    echo($this->makeSpaceString($this->sign_space).$this->result."\r\n");
    echo("\r\n");
    unset($this->numbers[0]);
    unset($this->numbers[1]);
    $this->result=ltrim($this->result,' ');
    array_unshift($this->numbers,$this->result);
    return true;
  }

  private function reset()
  {
    $this->max_len_number=0;
    $this->helper='';
    $this->result='';
  }

  private function setMaxLenNumber(int $num): bool
  {
    if($num>$this->max_len_number)
    {
      $this->max_len_number=$num;
      return true;
    }
    return false;
  }

  private function checkMinNumbers(): bool
  {
    if(count($this->numbers)>=2)
    {
      return true;
    }
    return false;
  }

  private function operSum(string &$arg1, string &$arg2): bool
  {
    if(empty($arg1) || empty($arg2)) return false;
    $arg=array(&$arg1,&$arg2);
    $this->reset();
    foreach($arg AS $num)
    {
      $this->setMaxLenNumber(strlen($num));
    }
    $this->setMaxLenNumber($this->max_len_number+$this->result_addition);
    $arg=$this->resizeString($arg,$this->max_len_number);
    $this->helper=$this->resizeString($this->helper,$this->max_len_number);
    $this->result=$this->resizeString($this->result,$this->max_len_number);

    for($i=($this->max_len_number-1);$i>=0;$i--)
    {
      $sum=0;
      foreach($arg AS $num)
      {
        $sum+=(int)$num[$i];
      }
      $sum+=(int)$this->helper[$i];
      $sum_s=(string)$sum;
      if(strlen($sum_s)==2)
      {
        $this->helper[$i-1]=$sum_s[0];
        $this->result[$i]=$sum_s[1];
      }
      else
      {
        $this->helper[$i-1]=0;
        $this->result[$i]=$sum_s[0];
      }
    }
    return true;
  }

  private function makeSpaceString(int $num): string
  {
    $str='';
    for($i=0;$i<$num;$i++)
    {
      $str.=' ';
    }
    return $str;
  }

  private function resizeString($arg, int $dstlen)
  {
    if(is_array($arg))
    {
      foreach($arg AS &$num)
      {
        $num_len=strlen($num);
        if($num_len<$dstlen)
        {
          $num=$this->makeSpaceString($dstlen-$num_len).$num;
        }
      }
    }
    else
    {
      $arg_len=strlen($arg);
      if($arg_len<$dstlen)
      {
        $arg=$this->makeSpaceString($dstlen-$arg_len).$arg;
      }
    }
    return $arg;
  }
}