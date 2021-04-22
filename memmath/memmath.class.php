<?php

/**
 * Math in memory
 */
class memmath
{
    /**
     * Numbers to operations
     * @var string[]
     */
    private $numbers=array();
    /**
     * Max length string
     * @var int
     */
    private $max_len_number=0;
    /**
     * Additional space for sign
     * @var int
     */
    private $sign_space=2; // ex. '+ '
    /**
     * Place to keep additional math operations
     * @var string
     */
    private $helper='';
    /**
     * Result of operations
     * @var string
     */
    private $result='';
    /**
     * Additional space for bigger math score (bigger than numbers)
     * @var int
     */
    private $result_addition=2; // min 1

    /**
     * Add numbers to math operations
     * @param int|string $num
     */
    public function addNumber($num): void
    {
        $num=(string)((int)$num);
        $this->numbers[]=$num;
    }

    /**
     * Make sum operations and display
     * @return bool
     */
    public function sum(): bool
    {
        if (!$this->checkMinNumbers()) {
            return false;
        }
        $this->operSum($this->numbers[0], $this->numbers[1]);

        $this->helper=str_replace('0', ' ', $this->helper);
        echo($this->makeSpaceString($this->sign_space).$this->helper."\r\n");
        echo($this->makeSpaceString($this->sign_space).$this->numbers[0]."\r\n");
        $str=$this->makeSpaceString($this->sign_space).$this->numbers[1]."\r\n";
        $str[0]='+';
        echo($str);

        for ($i=0;$i<($this->max_len_number+$this->sign_space);$i++) {
            echo('-');
        }
        echo("\r\n");
        for ($i=0;$i<strlen($this->result);$i++) {
            if ($this->result[$i]=='0') {
                $this->result[$i]=' ';
            } else {
                break;
            }
        }
        echo($this->makeSpaceString($this->sign_space).$this->result."\r\n");
        echo("\r\n");
        unset($this->numbers[0]);
        unset($this->numbers[1]);
        $this->result=ltrim($this->result, ' ');
        array_unshift($this->numbers, $this->result);
        return true;
    }

    /**
     * Reset all variables
     */
    private function reset(): void
    {
        $this->max_len_number=0;
        $this->helper='';
        $this->result='';
    }

    /**
     * Set variable max_len_number
     * @param int $num
     * @return bool
     */
    private function setMaxLenNumber(int $num): bool
    {
        if ($num>$this->max_len_number) {
            $this->max_len_number=$num;
            return true;
        }
        return false;
    }

    /**
     * Checks minimum amount of numbers for operations
     * @return bool
     */
    private function checkMinNumbers(): bool
    {
        if (count($this->numbers)>=2) {
            return true;
        }
        return false;
    }

    /**
     * Make math sum operations
     * @param string $arg1 Number 1
     * @param string $arg2 Number 2
     * @return bool
     */
    private function operSum(string &$arg1, string &$arg2): bool
    {
        if (empty($arg1) || empty($arg2)) {
            return false;
        }
        $arg=array(&$arg1,&$arg2);
        $this->reset();
        foreach ($arg as $num) {
            $this->setMaxLenNumber(strlen($num));
        }
        $this->setMaxLenNumber($this->max_len_number+$this->result_addition);
        $arg=$this->resizeString($arg, $this->max_len_number);
        $this->helper=$this->resizeString($this->helper, $this->max_len_number);
        $this->result=$this->resizeString($this->result, $this->max_len_number);

        for ($i=($this->max_len_number-1);$i>=0;$i--) {
            $sum=0;
            foreach ($arg as $num) {
                $sum+=(int)$num[$i];
            }
            $sum+=(int)$this->helper[$i];
            $sum_s=(string)$sum;
            if (strlen($sum_s)==2) {
                $this->helper[$i-1]=$sum_s[0];
                $this->result[$i]=$sum_s[1];
            } else {
                $this->helper[$i-1]=0;
                $this->result[$i]=$sum_s[0];
            }
        }
        return true;
    }

    /**
     * Make an empty string
     * @param int $num How many space
     * @return string
     */
    private function makeSpaceString(int $num): string
    {
        $str='';
        for ($i=0;$i<$num;$i++) {
            $str.=' ';
        }
        return $str;
    }

    /**
     * Resize string to new length
     * @param string $arg Source string
     * @param int $dstlen Destination length
     * @return string
     */
    private function resizeString($arg, int $dstlen)
    {
        if (is_array($arg)) {
            foreach ($arg as &$num) {
                $num_len=strlen($num);
                if ($num_len<$dstlen) {
                    $num=$this->makeSpaceString($dstlen-$num_len).$num;
                }
            }
        } else {
            $arg_len=strlen($arg);
            if ($arg_len<$dstlen) {
                $arg=$this->makeSpaceString($dstlen-$arg_len).$arg;
            }
        }
        return $arg;
    }
}
