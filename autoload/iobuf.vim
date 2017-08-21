let s:lib = expand('<sfile>:h:h') . '/iobuf.dll'

function! iobuf#nobuffer(job)
  if !has('win32') || !has('win64')
    return
  endif
  echo libcallnr(s:lib, 'no_buffer', job_info(a:job).process)
endfunction
