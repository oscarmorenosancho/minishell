/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edomingu <edomingu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:30:47 by omoreno-          #+#    #+#             */
/*   Updated: 2023/05/22 17:44:06 by edomingu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# define DOMOSH "DomoShell"
# define PROMPT "DomoShell $> "
# define SUBPROMPT "> "

# define MSG_DOMOSH "DomoShell: "
# define MSG_IS_DIRECTORY ": is a directory\n"
# define MSG_COLON ": "
# define MSG_CMD_NOT_FOUND "command not found\n"

# define MSG_SHLVL_INI "DomoShell: warning: shell level ("
# define MSG_SHLVL_END ") too high, resetting to 1\n"

# define ERROR_UNCLOSED_QUOTES "DomoShell: unclosed quotes\n"
# define ERROR_CD_HOME "DomoShell: cd: HOME not set\n"
# define ERROR_SYN_PIPE "DomoShell: syntax error near unexpected token `|'\n"
# define ERROR_SYN_REDIR "DomoShell: syntax error near unexpected token `"
# define ERROR_SYN_NL "DomoShell: syntax error near unexpected token `newline'\n"
# define ERROR_NVI_INI "DomoShell: export: `"
# define ERROR_NVI_END "': not a valid identifier\n"
# define ERROR_OLDPWD_NS "DomoShell: cd: OLDPWD not set\n"
# define ERROR_PWD_NS "DomoShell: pwd: PWD not set\n"
# define ERROR_CALLOC "DomoShell: cd: calloc error\n"
# define ERROR_GETCWD "cd: error retrieving current directory: getcwd: cannot access \
parent directories: No such file or directory\n"

# define PERROR_CD "DomoShell: cd: "

#endif
