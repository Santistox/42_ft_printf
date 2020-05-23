#include "ft_printf.h"

/*
** function copy numbers form num1 array to num2 array
*/

void copy_int(int *num1, int *num2, int bit)
{
    int i;
 
    i = bit;
    while (--i >= 0)
        num1[i] = num2[i];
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
	int *bits;

	bits = new_arr(0,3);
	bits[0] = bit;
	bits[1] = bit;
	bits[2] = bit;
	num1 = new_arr(num, bits[0]);
	num2 = new_arr(num, bits[1]);
	res = new_arr(0, bits[2]);
	while (pow-- > 1)
	{
		reset_int(res, bit);
		mult_by_column(num1, num2, res, bits);
		copy_int(num1, res, bit);
	}
	free(num1);
	free(num2);
	free(bits);
	return(res);
}

/*
**	create int array and stack each character of number to cell
*/

int *new_arr(ull_t num, int bit)
{
	int i;
	int *arr;

	i = bit - 1;
	if (!(arr = malloc(sizeof(int *) * bit)))
		malloc_error();
	if (!(arr = ft_memset(arr, 0, bit)))
		malloc_error();
	while (i >= 0 && num >= 0)
	{
		arr[i] = num % 10;
		num /= 10;
		i--;
	}
	return (arr);
}
// заранее чeкаем пресишн есть вообще
int *prec(int *num, int prec, t_fenv *fenv) //int prec, int compos, int bit)
{
	int *add;
	int *res;
	int extra;
	int compos;

//	compos = (fenv->compos > 0 ? fenv->compos : fenv->compos);
	compos = fenv->compos;
	extra = (compos + prec == 0) ? 2 : 1; 
	if (fenv->compos + prec >= fenv->res_bit || !num)
		return (num);
	if (num[fenv->compos + prec] < 5)
		return (num);
	add = new_arr(0, compos + prec + extra);
	add[compos + prec + extra - 1] = 1;
//	print_num(add, compos + prec + extra, '\n');
	res = new_arr(0, compos + prec + extra);
	int *res_bit = new_arr(0, 1);
	res_bit[0] = compos + prec + extra - 1;
	res_bit[1] = compos + prec + extra;
	add_by_column(num, add, res, res_bit);
//	print_num(res, compos + prec + extra, '\n');
	free(num);
	free(add);
	if (cut_num(&res, compos + prec + extra) == compos + prec + extra)
		fenv->compos++;
	return (res);
}

/*
**	move float number to buffer from int array
*/

void	to_buff_float(t_env *env, t_fenv *fenv, int *num)
{
	int  i;
	int prec;

	i = 0;
	prec = env->precision;
	/*
	while (i <= fenv->res_bit && num[i] == 0 && i + 1 < fenv->compos)
		i++;
	*/
	if (fenv->compos <= 0)
	{
		to_buff_char('0', env);
		if (prec != 0)
			to_buff_char('.', env);
		while ((fenv->compos)++ < 0 && prec > 0)
		{
			to_buff_char('0', env);
			prec--;
		}
		while (prec-- > 0)
		{
			to_buff_char(num[i] + '0', env);
			i++;
		}
	}
	else
	{
		while (i < fenv->res_bit && i < fenv->compos + env->precision)
		{
			if (i == fenv->compos)
				to_buff_char('.', env);
			to_buff_char(num[i] + '0', env);
			i++;
		}
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

void free_fenv(t_fenv *fenv)
{
	fenv->bit = 0;
	fenv->sign = 0;
	fenv->res_bit = 0;
	fenv->compos = 0;
	fenv->exp_num = 0;
	fenv->mant_num = 0;
	fenv->exp = 0;
	fenv->exp_res = 0;
	free(fenv->bits);
	//fenv->bits = NULL; эта херня почему-то течет 
}

t_fenv *init_fenv(int bit, ul_t num)
{
	t_fenv *fenv;

	if (!(fenv = ft_memalloc(sizeof(t_fenv))))
		malloc_error();
	fenv->bit = bit;
	fenv->res_bit = bit;
	if (num == 0)
	{
		fenv->exp_num = 0; 
		fenv->mant_num = 0;
		fenv->sign = 0;
		fenv->exp = 0;
		fenv->compos = 1; 
		return (fenv);
	}
	fenv->exp_num = 1023; 
	fenv->mant_num = 52;
	fenv->sign = num >> (bit - 1);
	fenv->exp = num << 1; // 
	fenv->exp = fenv->exp >> (fenv->mant_num + 1);
	fenv->exp_res = fenv->exp - (fenv->exp_num);
	fenv->compos = fenv->bit - (fenv->mant_num - fenv->exp_res);
	return (fenv);
}

/*
** write formatted result to buffer
*/

void	float_output(t_env *env, t_fenv *fenv, int *res)
{
	env->offset -= num_size(env, fenv, res);
	if (fenv->sign && env->zero)
		to_buff_char('-', env);
	env->offset -= (fenv->sign && !env->space) ? 1 : 0;
	env->offset -= (!fenv->sign && env->plus) ? 1 : 0;
	if (!env->minus && !env->zero)
		to_buff_offset(env);
	if (env->plus && !fenv->sign)
		to_buff_char('+', env); 
	if (fenv->sign && !env->zero)
		to_buff_char('-', env); 
	if (!fenv->sign && env->space && !env->plus)
		to_buff_char(' ', env);
	if (env->zero)
		put_zero(env); 
	to_buff_float(env, fenv, res);
	if (env->precision == 0 && env->grille)
		to_buff_char('.', env);
	env->offset -= (env->precision == 0 && env->grille) ? 1 : 0;
	if (env->minus)
		to_buff_offset(env);
}

void	float_zero(t_fenv *fenv, t_env *env)
{
	int *res;
	int i;

	i = 0;
	if (!env->is_precision)
	{
		env->is_precision = 1;
		env->precision = 6;
	}
	if (!(res = (int*)malloc(sizeof(int*) * env->precision)))
		return ;
	while (i < env->precision)
	{
		res[i] = 0;
		i++;
	}
	fenv->compos = -1;
	float_output(env, fenv, res);
}

int 	valid_float(t_fenv *fenv, ull_t mant)
{
	if (fenv->mant_num - fenv->exp_res == -972 && mant == 4503599627370496 && fenv->sign == 0)
		return (1);
	else if (fenv->mant_num - fenv->exp_res == -972 && mant == 4503599627370496 && fenv->sign == 1)
		return (2);
	else if (fenv->mant_num - fenv->exp_res == -972 && mant == 6755399441055744)
		return (3);
	return (0);
}

// эту функцию нужно будет доработать - взаимодействие инф/-инф/нан с разными +-# и тд

void put_unval(t_fenv **fenv, t_env *env, int error)
{
	char *str;

	str = (error != 1 ? (error == 2 ? ft_strdup("-inf") : ft_strdup("nan")) : ft_strdup("inf"));
	to_buff_str(str, env);
	free_fenv(*fenv);
	free(*fenv);
}

void	flag_f(t_env *env, va_list args)
{
	t_fenv *fenv; // структура флота
	ul_t *ptr; // указатель на число
	ull_t mant; // мантисса
	double	cont; // контейнер с числом, вытаскиваем с ва_аргс
	int error; // ошибка, для inf/-inf/nan

	error = 0;
	cont = (double)va_arg(args, double);
	ptr = (ul_t *)&cont;
	fenv = init_fenv(64, *ptr);
	if (*ptr == 0) // если число == 0
	{
		float_zero(fenv, env);
		free_fenv(fenv);
		free(fenv);
		return ;
	}
	mant = *ptr & 4503599627370495; // вытаскиваем мантиссу
	mant = mant | 4503599627370496;
	error = valid_float(fenv, mant); // проверяем не инф/нан ли это число
	if (error)
		return put_unval(&fenv, env, error); // если да, то переходим в другую функцию

	// это можно вынести в новую функцию

	int *arr = new_arr((ull_t)mant, fenv->bit); // массив с манитос, подготовка к умножению
	int *n; //массив с числом в степени
	n = NULL; 
	fenv->bits = new_arr(0,3); // размер массивов
	fenv->bits[0] = fenv->bit;
	fenv->bits[1] = 2 * fenv->bit;
	fenv->bits[2] = fenv->bits[0] + fenv->bits[1];
	int bit = fenv->bit; 
	if (fenv->mant_num - fenv->exp_res >= 0) //создаем массив т
		n = binpow(5, fenv->mant_num - fenv->exp_res, fenv->bits[1]);
	else
		n = binpow(2, fenv->exp_res - fenv->mant_num, fenv->bits[1]);
	fenv->bit = bit;
	int *res = new_arr((ull_t)0, fenv->bits[2]); //результатирующий массив
	mult_by_column(arr, n, res, fenv->bits);
	fenv->bits[2] = cut_num(&res, fenv->bits[2]);
	fenv->res_bit = fenv->bits[2];
	
	fenv->compos = fenv->res_bit - (fenv->mant_num - fenv->exp_res);
	if (!env->is_precision) //задаем присишн
	{
		env->is_precision = 1;
		env->precision = 6;
	}
	res = prec(res, env->precision, fenv); //округление
	float_output(env, fenv, res); //загоняем в буф
	
	free_fenv(fenv); //освобождаем
	free(arr);
	free(n);
	free(res);
	free(fenv);
}