const $ = s => document.querySelector(s);
const aEl = $('#a'), bEl = $('#b'), resultEl = $('#result'), statusEl = $('#status');

function parse(s){
  s=s.trim();
  if(!/^[+-]?\d+$/.test(s)) throw new Error('Digite um inteiro válido.');
  return BigInt(s);
}
function factorial(N){ if(N<0n) throw new Error('O fatorial não é calculado para números negativos.'); if(N>5000n) throw new Error('Limite visual: escolha um valor ≤ 5000 para o fatorial.'); let r=1n; for(let n=2n;n<=N;n++)r*=n; return r; }
function show(value, note='') { resultEl.textContent=String(value); statusEl.textContent=note; statusEl.className='status'; }
function fail(e){ resultEl.textContent='Erro'; statusEl.textContent=e.message||String(e); statusEl.className='status error'; }
function op(name){
  try{
    const A=parse(aEl.value), B=parse(bEl.value); let r, note='';
    switch(name){
      case 'add': r=A+B; break; case 'sub': r=A-B; break; case 'mul': r=A*B; break;
      case 'div': if(B===0n) throw new Error('Divisão por zero.'); r=A/B; break;
      case 'mod': if(B===0n) throw new Error('Divisão por zero.'); r=A%B; break;
      case 'factA': r=factorial(A); note='Fatorial de A.'; break; case 'factB': r=factorial(B); note='Fatorial de B.'; break;
      case 'lt': r=A<B; break; case 'eq': r=A===B; break; case 'gt': r=A>B; break;
      case 'abs': r=A<0n?-A:A; break; case 'neg': r=-A; break; case 'inc': r=A+1n; break; case 'dec': r=A-1n; break;
      case 'shl': if(B<0n || B>100000n) throw new Error('O deslocamento precisa estar entre 0 e 100000.'); r=A*10n**B; break;
      case 'shr': if(B<0n || B>100000n) throw new Error('O deslocamento precisa estar entre 0 e 100000.'); r=A/(10n**B); break;
      case 'toint': { const min=-(2n**63n), max=2n**63n-1n; if(A<min||A>max) throw new Error('Overflow: valor fora do intervalo de long long.'); r=A; note='Representável em long long.'; break; }
      default: throw new Error('Operação desconhecida.');
    }
    show(r,note);
  }catch(e){fail(e)}
}
document.querySelectorAll('[data-op]').forEach(b=>b.addEventListener('click',()=>op(b.dataset.op)));
$('#copy').addEventListener('click',async()=>{try{await navigator.clipboard.writeText(resultEl.textContent);statusEl.textContent='Resultado copiado.';statusEl.className='status'}catch{statusEl.textContent='Não foi possível copiar automaticamente.'}});
