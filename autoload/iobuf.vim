let s:lib = expand('<sfile>:h:h') . '/iobuf.dll'

function! iobuf#nobuffer(job)
  if !has('win32') || !has('win64')
    return
  endif
  let pid = split(string(a:job), ' ')[1]
  call libcallnr(s:lib, 'no_buffer', 0+pid)
endfunction
