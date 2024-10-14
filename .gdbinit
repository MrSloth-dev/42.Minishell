define swap
break ft_swap_env
display i
display cmdargs
display shell->envp[k]
display temp[k]
end
define env
break ft_env_exist
display var
display j
display key
display name
display len
display index
end

define cd
break ft_cd
break ft_update_directory
run cd
display update_old
display cmdargs[1]
display old_pwd
end

define export
display cmdargs[k]
display temp[k]
end

define run_x
break ft_export
run "export ZSH+=:lol"
end

define run_s
break ft_export
run "export USER=joao-polo iol=ganda_merda clix=merda_mesmo"
end

define run_u
run "export unset USER ZSH"
end

define tokenizer
break ft_tokenizer
run
display i
end

define bin
break ft_make_binary_tree
run
end

define run_cd
break ft_cd
run "cd "
display getcwd(0 , 0)
display *cmdargs @3
end

# Some notes and useful commands
# info locals get vars
# info args
# info inferiors get process, need to cancel detach of parents
