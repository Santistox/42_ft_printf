#include "ft_printf.h"
/*
void ft_putchar(char c)
{
	write(1, &c, 1);
}

double	ft_pow(double n, int pow)
{
	return (pow ? n * ft_pow(n, pow - 1) : 1);
}

int		ft_first(uint64_t n)
{
	int		i;

	i = 1;
	while (n > 0)
	{
	//	printf(" - %d\n", num);
		i = n % 10;
		n /= 10;
	}
	return (i);
}
*/

/*
** function copy numbers form num1 array to num2 array
*/

void copy_int(int *num1, int *num2, int bit)
{
	int i;

	i = bit;
	while (i-- >= 0)
		num2[i] = num1[i];
}

/*
** function reset to 0 numbers form int array
*/

void reset_int(int *num, int bit)
{
	int i;

	i = bit;
	while (i-- >= 0)
		num[i] = 0;
}

/*
** exponentiation of the number in the array
*/

int *binpow(int num, int pow, int bit)
{
	int *num1;
	int *num2;
	int *res;

	num1 = new_arr(num, bit);
	num2 = new_arr(num, bit);
	res = new_arr(0, bit);
	while (pow-- > 1)
	{
		reset_int(res, bit);
		mult_by_column(num1, num2, res, bit);
		copy_int(res, num1, bit);
	}
	free(num1);
	free(num2);
	return(res);
}

/*
**	create int array and stack each character of number to cell
*/

int *new_arr(long long unsigned int num, int bit)
{
	int i;
	int *arr;

	i = bit - 1;
	if (!(arr = malloc(sizeof(int *) * bit)))
		error(403);
	if (!(arr = ft_memset(arr, 0, bit)))
		error(403);
	while (i >= 0 && num >= 0)
	{
		arr[i] = num % 10;
		num /= 10;
		i--;
	}
	return (arr);
}
// заранее чeкаем чо пресишн есть вообще
int *prec(int *num, int prec, int compos, int bit)
{
	int *add;
	int *res;

	if (prec <= 0 || compos + prec >= bit || !num)
		return (num);
	if (num[compos + prec] < 5)
		return (num);
	add = new_arr(0, compos + prec);
	add[compos + prec - 1] = 1;
	res = new_arr(0, compos + prec);
	add_by_column(num, add, res, compos + prec);
	free(num);
	free(add);
	return (res);
}

/*
**	move float number to buffer from int array
*/

void	to_buff_float(t_env *env, t_fenv *fenv, int *num)
{
	int  i;

	i = 0;
	while (i <= fenv->bit && num[i] == 0)
		i++;
	while (i < fenv->bit && i < fenv->compos + env->precision)
	{
		if (i == fenv->compos)
			to_buff_char('.', env);
		to_buff_char(num[i] + '0', env);
		i++;
	}
}

/*
** determines the size of a number
*/

int 	num_size(t_env *env, t_fenv *fenv, int *num)
{
	int  i;
	int  k;

	i = 0;
	k = 0;
	while (i <= fenv->bit && num[i] == 0)
		i++;
	while (i < fenv->bit && i < fenv->compos + env->precision)
	{
		if (i == fenv->compos)
			k++;
		k++;
		i++;
	}
	return(k);
}

t_fenv *init_fenv(int bit, unsigned int num)
{
	t_fenv *fenv;

	if (!(fenv = ft_memalloc(sizeof(t_fenv))))
		error(403);
	fenv->bit = bit;
	if (bit == 32)
	{
		fenv->exp_num = 127;
		fenv->mant_num = 23;
	}
	else
	{
		fenv->exp_num = 1023; // это не тестила
		fenv->mant_num = 52;
	}
	fenv->sign = num >> (bit - 1);
	fenv->exp = num << 1; // 
	fenv->exp = fenv->exp >> (fenv->mant_num + 1);
	fenv->exp = fenv->exp - (fenv->exp_num);
	fenv->compos = fenv->bit - (fenv->mant_num - fenv->exp);
	return (fenv);
}

/*
** write formatted result to buffer
*/

void	float_output(t_env *env, t_fenv *fenv, int *res)
{
	int arg_size;

	arg_size = num_size(env, fenv, res);
	env->offset -= arg_size;
	if (fenv->sign && env->zero) // если у нас есть заполнение нулями и число отрицательное
		to_buff_char('-', env);  // то загоняем в буфер сначала минус  -00043.12300
	env->offset -= (fenv->sign && !env->space) ? 1 : 0; // убрираем лишний отступ при отрицательном значении
	if (!env->minus && !env->zero)
		to_buff_offset(env); // если отступ положительный, то мы его выводим
	if (env->plus && !fenv->sign)
		to_buff_char('+', env); // если число положительное, то выводим "+" 
	if (fenv->sign && !env->zero)
		to_buff_char('-', env); // если число отрицательное, то выводим "-" 
	if (!fenv->sign && env->space && !env->plus)
		to_buff_char(' ', env); // добиваем пробельчик если отступ пробелами
	if (env->zero)
		put_zero(env); // выводим нули перед числом  
	to_buff_float(env, fenv, res); // закидываю результат в буфер
	if (env->minus)
		to_buff_offset(env); // выводим отступ после
}

void	flag_f(t_env *env, va_list args)
{
	t_fenv *fenv;
	unsigned int *ptr;
	unsigned int num;
	unsigned int mant;
	float	cont;

	cont = va_arg(args, double);
	ptr = (unsigned int *)&cont;
	num = *ptr;
	fenv = init_fenv(32, *ptr);
	mant = num & 8388607;
	mant = mant | 8388608;

	/* DEBUG */
	printf("COMPOS is %i\n", fenv->compos);
	printf("MANT is %u\n", mant); 
	printf("EXP is %i\n", fenv->exp);
	printf("SIGN is %u\n", fenv->sign);


	int *arr = new_arr((long long unsigned int)mant, fenv->bit);
	int *n;
	n = NULL;
	if (23 - fenv->exp >= 0)
		n = binpow(5, 23 - fenv->exp, fenv->bit);
	else
		n = binpow(2, fenv->exp - 23, fenv->bit);

	/* DEBUG */
	print_num(arr, fenv->bit, '\n');
	print_num(n, fenv->bit, '\n');

	int *res = new_arr((long long unsigned int)0, fenv->bit);
	mult_by_column(arr, n, res, fenv->bit);

	/* DEBUG */
	print_num(res, fenv->bit, '\n');

	res = prec(res, env->precision, fenv->compos, fenv->bit); 
	
	/* DEBUG */
	print_num(res, fenv->compos + env->precision, '\n');

	/* KOLHOZING */
	float_output(env, fenv, res);


	printf("% 15.6f.\n",cont);
	free(arr);
	free(n);
	free(res);
	free(fenv);
}



























/*
void	flag_f(t_env *env, va_list args)
{
//	static const double	powers_of_10[] = {1, 10, 100, 1000, 10000, 100000,
//	1000000, 10000000, 100000000, 1000000000, 10000000000};
	double		num;
	uint32_t	whole;
	char		*res;
	int			minus;
	uint32_t			dig;
	int			i;
	uint64_t frac;
	int	leng;
	uint64_t	frac_before;
	uint32_t	temp;


	leng = 1;
	i = 0;
	minus = 0;
	env->precision = (env->is_precision) ? env->precision : 6;
	num = va_arg(args, double);
	if (num < 0.0f)
	{
		minus = 1;
		num *= -1;
	}
	whole = (uint32_t)num;
	printf("NUM is %f\n", ((num - whole) * ft_pow(10, env->precision + 1)));
	num = ((num - whole) * ft_pow(10, env->precision + 1));
	frac = (uint64_t)(num);
	frac_before = frac;
	printf("WHOLE is %u\n", whole);
	printf("NUM is %f\n", num);
	printf("FRAC is %llu\n", frac);
	
	frac = ((unsigned int)frac % 10 > 4) ? (frac) / 10 + 1 : frac / 10;
	if (ft_first(frac_before) > ft_first(frac) && ft_first(frac_before) > 4)
		whole++;
	temp = whole;
	if (temp == 0)
		leng++;
	while (temp && ++leng)
		temp /= 10;
	res = ft_memalloc(sizeof(char) * (leng + env->precision));
	while (i++ < (leng + env->precision - 1))
		res[i] = '0';
	res[i] = '\0';
	res[leng - 1] = (env->precision > 0) ? '.' : (env->offset - leng > 1 && env->minus) ? ' ' : '\0';
	i = leng - 2;
	temp = whole;
	printf("WHOLE is %u\n", temp);
	while (i >= 0)
	{
		dig = temp % 10;
		res[i--] = dig + '0';
		temp /= 10;
	}
	i = leng + env->precision - 1;
	printf("%llu\n", frac);
	printf("%d %d\n", ft_first(frac_before), ft_first(frac));
	while (i > leng - 1)
	{
		dig = (uint64_t)frac % 10;
		res[i--] = dig + '0';
		frac /= 10;
	//	printf("%i\n", dig);
	}
	if (env->zero > 0)
	{
		res = zero_offset(env, res, minus);
		plus_minus(env, &res, minus, 0);
	}
	else if (env->offset > 0)
	{
		plus_minus(env, &res, minus, 0);
		if (minus)
			res = ft_strjoin("-", res);
		res = space_offset(env, res, 0, 0);
	}
	if (minus && res[0] != '-' && res[env->offset - leng - env->precision - 1] != '-')
		res = ft_strjoin("-", res);
	if (env->space && !minus)
		res = ft_strjoin(" ", res);
	env->buf = ft_strjoin(env->buf, res);
}*/
/*
void	flag_f(t_env *env, va_list args)
{
	static const double	powers_of_10[] = {1, 10, 100, 1000, 10000, 100000,
	1000000, 10000000, 100000000, 1000000000};
	uint32_t			whole;
	uint32_t			frac;
	double		num;
	long		tmp;
	int			leng;
	char		*res;
	int			i;
	int			dig;
	double		rest;
	double		rest_before;
	int			minus;

	leng = 1;
	i = 0;
	dig = 0;
	minus = 0;
	env->precision = (env->is_precision) ? env->precision : 6;
	num = va_arg(args, double);

	whole = (uint32_t)num;
	num = (num - whole) * powers_of_10[env->precision - 1];
	frac = (uint32_t)(num);
	printf("WHOLE is %u\n", whole);
	printf("NUM is %f\n", num);
	printf("FRAC is %u\n", frac);

	if (num < 0.0f)
	{
		minus = 1;
		num *= -1;
	}
	tmp = (long)num;
	if (tmp == 0)
		leng++;
	while (tmp && ++leng)
		tmp /= 10;
	res = ft_memalloc(sizeof(char) * (leng + env->precision));
	while (i++ < (leng + env->precision - 1))
		res[i] = '0';
	res[i] = '\0';
//	res[leng - 1] = '.';
	res[leng - 1] = (env->precision > 0) ? '.' : (env->offset - leng > 1 && env->minus) ? ' ' : '\0';
	i = leng - 2;
	tmp = (long)num;
	while (i >= 0)
	{
		dig = tmp % 10;
		res[i--] = dig + '0';
		tmp /= 10;
	}
	//printf("%f\n", (num - (long)num)* ft_pow(10, env->precision + 1));
	rest = (num - (long)num) * ft_pow(10, env->precision + 1);
	printf("rest before is %f\n", rest);
	rest_before = rest;
	rest = ((int)rest % 10 > 4) ? (rest) / 10 + 1 : rest / 10;
	if (ft_first(rest_before) > ft_first(rest) && ft_first(rest_before) > 4)
	{
		res[leng - 2] += 1;
		if (!ft_isdigit(res[leng - 2]))
			res[leng - 2] = '0';
		// сделать функцию - иттеративно прохожу по числу и увеличиваю по условию ifdigit
	}
	printf("rest %f\n", rest);
	printf("%d %d\n", ft_first(rest_before), ft_first(rest));
	i = leng + env->precision - 1;
	while (i > leng - 1)
	{
		dig = (int)rest % 10;
		res[i--] = dig + '0';
		rest /= 10;
	}
	if (env->zero > 0)
	{
		res = zero_offset(env, res, minus);
		plus_minus(env, &res, minus, 0);
	}
	else if (env->offset > 0)
	{
		plus_minus(env, &res, minus, 0);
		if (minus)
			res = ft_strjoin("-", res);
		res = space_offset(env, res, 0, 0);
	}
	if (minus && res[0] != '-' && res[env->offset - leng - env->precision - 1] != '-')
		res = ft_strjoin("-", res);
	//if (env->space && !minus && env->minus)
	//	res = ft_strjoin(res, " ");
	if (env->space && !minus)
		res = ft_strjoin(" ", res);
	env->buf = ft_strjoin(env->buf, res);
}
*/
/*
static inline void		fast_dtoa_roundup(double diff, int prec,
						uint32_t *whole, uint32_t *frac)
{
	static const double	powers_of_10[] = {1, 10, 100, 1000, 10000, 100000,
	1000000, 10000000, 100000000, 1000000000};
​
	if (diff > 0.5
	|| (diff == 0.5 && prec > 0 && (*frac & 1))
	|| (diff == 0.5 && prec == 0 && (*whole & 1)))
	{
		(*frac)++;
		if (*frac >= powers_of_10[prec])
		{
			*frac = 0;
			(*whole)++;
		}
	}
}
​
static inline char		*fast_dtoa_print(uint32_t whole, uint32_t frac,
						char *buff, int prec)
{
	register int_fast16_t	count;
	register char			*ptr;
​
	count = prec;
	ptr = buff;
	while (count-- > 0)
	{
		*ptr++ = (char)('0' + (frac % 10));
		frac /= 10;
	}
	if (frac > 0)
		++whole;
	if (prec > 0)
		*ptr++ = '.';
	*ptr++ = (char)(48 + (whole % 10));
	while (whole /= 10)
		*ptr++ = (char)(48 + (whole % 10));
	*ptr = 0;
	return (ptr);
}
​
static inline size_t	ft_fast_dtoa(double val, char *buff,
						int prec)
{
	static const double	powers_of_10[] = {1, 10, 100, 1000, 10000, 100000,
	1000000, 10000000, 100000000, 1000000000};
	register char		*ptr;
	uint32_t			whole;
	uint32_t			frac;
​
	if (val < 0.0 || val != val)
		return (0);
	whole = (uint32_t)val;
	val = (val - whole) * powers_of_10[prec];
	frac = (uint32_t)(val);
	fast_dtoa_roundup(val - frac, prec, &whole, &frac);
	ptr = fast_dtoa_print(whole, frac, buff, prec);
	ft_strrev(buff, ptr - 1);
	return ((size_t)(ptr - buff));
}

void	flag_f(t_env *env, va_list args)
{
	double		num;
	size_t		to_print;
	
	num = va_arg(args, double);
	to_print = ft_fast_dtoa(num, env->buf, env->precision);
}*/