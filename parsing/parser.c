/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 17:28:35 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/15 17:30:58 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*⭐ Parser
>- Si les quote " " ou ' ' ne sont pas fermé alors return une erreur sytax.
>
Si les caractère spéciaux tels que "\" ou ";" return une erreur sytax.
>
Gérer ' ' qui doit empêcher le shell d’interpréter les méta-caractères
présents dans la séquence entre guillemets.
>
Gérer " " qui doit empêcher le shell d’interpréter les méta-caractères
présents dans la séquence entre guillemets sauf le $.
>
Gérer les pipes | en dehors des Quotes.
#/
