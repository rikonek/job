<?php

declare(strict_types=1);

interface MemmathIf
{
    public function addNumber(string $number);
    public function sum();
}

class MemStruct
{
    /**
     * Numbers to operations
     * @var array
     */
    public array $numbers;
    /**
     * Result of operations
     * @var string
     */
    public string $result = '';
    /**
     * Place to keep additional math operations
     * @var string
     */
    public string $helper = '';

    public function __construct(...$numbers)
    {
        if (!is_array($numbers)) {
            throw new Exception('At least two numbers are required!');
        }
        $this->numbers=$numbers;
    }
}

/**
 * Math in memory
 */
class Memmath implements MemmathIf
{
    /** Additional space for sign */
    private const SIGN_SPACE=2;

    /**
     * Numbers to operations
     * @var string[]
     */
    private array $numbers=array();

    /**
     * Resize string to new length
     * @param string|array $arg Source string
     * @param int $dstlen Destination length
     */
    private function resizeString(&$arg, int $dstlen): void
    {
        if (is_array($arg)) {
            foreach ($arg as &$num) {
                $num=str_pad($num, $dstlen, ' ', STR_PAD_LEFT);
            }
        } else {
            $arg=str_pad($arg, $dstlen, ' ', STR_PAD_LEFT);
        }
    }

    /**
     * Push front number
     * @param string $number
     * @return void
     */
    private function pushFrontNumber(string $number): void
    {
        array_unshift($this->numbers, $number);
    }

    /**
     * Push back number
     * @param string $number
     * @return void
     */
    private function pushBackNumber(string $number): void
    {
        $this->numbers[]=$number;
    }

    /**
     * Pop number
     * @return string|null
     */
    private function popNumber(): ?string
    {
        return array_shift($this->numbers);
    }

    /**
     * Add numbers to math operations
     * @param string $number
     * @return void
     */
    public function addNumber(string $number): void
    {
        $this->pushBackNumber((string)((int)$number));
    }

    /**
     * Make math sum operations
     * @param MemStruct $s
     * @return bool
     */
    private function operSum(MemStruct &$s): bool
    {
        $max_len_number=strlen((string) array_sum($s->numbers));
        $this->resizeString($s->numbers, $max_len_number + self::SIGN_SPACE);
        $this->resizeString($s->result, $max_len_number + self::SIGN_SPACE);
        $this->resizeString($s->helper, $max_len_number + self::SIGN_SPACE);

        for ($i=($max_len_number + self::SIGN_SPACE - 1); $i>=0; $i--) {
            $sum=0;
            foreach ($s->numbers as $num) {
                $sum+=(int) $num[$i];
            }
            $sum+=(int) $s->helper[$i];
            $sum_str=(string) $sum;
            if (strlen($sum_str)==2) {
                $s->helper[$i-1]=$sum_str[0];
                $s->result[$i]=$sum_str[1];
            } else {
                $s->helper[$i-1]=' ';
                $s->result[$i]=$sum_str[0];
            }
        }
        $s->result=ltrim($s->result, '0');
        $this->resizeString($s->result, $max_len_number + self::SIGN_SPACE);
        return true;
    }

    /**
     * Make sum operations and display
     * @return bool
     */
    public function sum(): bool
    {
        $a=$this->popNumber();
        $b=$this->popNumber();
        if (is_null($a) || is_null($b)) {
            return false;
        }
        $s=new MemStruct($a, $b);
        $this->operSum($s);

        $last=array_key_last($s->numbers);
        $s->numbers[$last][0]='+';

        echo($s->helper . PHP_EOL);
        echo(implode(PHP_EOL, $s->numbers) . PHP_EOL);
        echo(str_repeat('-', strlen($s->result)) . PHP_EOL);
        echo($s->result . PHP_EOL);
        echo(PHP_EOL);

        $this->pushFrontNumber($s->result);
        return true;
    }
}
