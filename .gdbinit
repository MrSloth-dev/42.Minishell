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

define run_s
break ft_export
run "export USER=joao-polo iol=ganda_merda clix=merda_mesmo"
end

define run_u
run "export unset USER ZSH"
end

# info locals
# info args
