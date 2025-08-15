/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_metachar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeimoun <pmeimoun@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:38:37 by pmeimoun          #+#    #+#             */
/*   Updated: 2025/08/15 22:22:50 by pmeimoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Gérer ' ' qui doit empêcher le shell d’interpréter les méta-caractères
présents dans la séquence entre guillemets.

Gérer " " qui doit empêcher le shell d’interpréter les méta-caractères
présents dans la séquence entre guillemets sauf le $.

Gérer les pipes | en dehors des Quotes.
*/

#include "minishell.h"


