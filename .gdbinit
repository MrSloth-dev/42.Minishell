define swap
break ft_swap_env
display i
display cmdargs
display shell->envp[k]
display temp[k]
end

define export
display cmdargs[k]
display temp[k]
end

define run
run "export USER=joao-polo iol=ganda_merda"
end


# info locals
# info args
